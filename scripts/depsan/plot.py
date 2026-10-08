#!/usr/bin/env python3
"""Generate PDF plots from DepSan analysis results."""

import argparse
import glob
import json
import os
import sys
import warnings

import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
from matplotlib import ticker
from matplotlib.patches import ConnectionPatch

warnings.filterwarnings("ignore")

HATCHES = ["//////", "......", "", "\\\\\\\\\\\\", "xxxxxx", "OOOOOO", "++++"]
DEP_ORDER = ["Data Dependency", "Address Dependency", "Control Dependency"]
DEP_SHORT = {"Control Dependency": "Control",
             "Data Dependency": "Data",
             "Address Dependency": "Address"}
DEP_TITLES = {"Control Dependency": "#Control dependencies",
              "Data Dependency": "#Data dependencies",
              "Address Dependency": "#Address dependencies"}
FINISHED_RESULTS = {"PASS", "UNKNOWN", "FAIL"}
LK_PASSES = {"LKMMAnnotateHook": "Pre-optimization",
              "LKMMAnnotateDepsPass": "Post-optimization",
              "LKMMVerifyDepsPass": "Matching"}

BAR_STYLES = [
    ("black", ""),            # solid black
    ("white", "//////"),      # forward slash
    ("white", ""),            # solid white
    ("white", "\\\\\\\\\\\\"),  # backward slash
]

# Fixed style mapping for dependency types (consistent across all dep plots)
DEP_STYLES = {
    "Data Dependency": ("black", ""),            # solid black
    "Address Dependency": ("white", "//////"),   # forward slash
    "Control Dependency": ("white", ""),          # solid white
    "Data": ("black", ""),
    "Address": ("white", "//////"),
    "Control": ("white", ""),
}


# -- Sizing presets ----------------------------------------------------------

PAPER = {
    "percentage": (5, 1),
    "da_times": (5, 2),
    "dep_sources": (10, 2),
    "dep_sinks": (10, 4),
    "dep_hist": (5, 1.5),
    "sa_times": (5, 1.5),
    "font_size": 12,
    "context": "paper",
}

PAPER_BW = {
    "percentage": (5.91, 1.18),
    "da_times": (5.91, 2.36),
    "dep_sources": (5.91, 1.18),
    "dep_sinks": (5.91, 2.36),
    "dep_hist": (5.91, 1.77),
    "sa_times": (5.91, 1.77),
    "font_size": 8,
    "context": "paper",
}

SLIDE = {
    "percentage": (10, 2.5),
    "da_times": (10, 4),
    "dep_sources": (14, 3),
    "dep_sinks": (14, 5),
    "dep_hist": (10, 3),
    "sa_times": (10, 3),
    "font_size": 18,
    "context": "talk",
}


# -- Global BW state (set in main) ------------------------------------------

BW = False
SUFFIX = ""


def get_palette(n=None):
    if BW:
        return sns.color_palette("Greys", n_colors=n) if n else "Greys"
    return sns.color_palette("pastel", n_colors=n) if n else sns.color_palette("pastel")


def setup_style(sz):
    if BW:
        mpl.rcParams["pdf.fonttype"] = 42
        mpl.rcParams["ps.fonttype"] = 42
        mpl.rcParams["hatch.linewidth"] = 0.5
        mpl.rcParams["hatch.color"] = "black"
        mpl.rcParams["figure.labelsize"] = 8
        sns.set_style("ticks", {"xtick.major.size": 8, "ytick.major.size": 8, "axes.grid": True})
        sns.set_context("paper", rc={"font.size": 8, "axes.titlesize": 8, "axes.labelsize": 8})
    else:
        plt.rcParams["font.size"] = sz["font_size"]


def apply_bw_bars(patches, legend_handles=None):
    """Apply BAR_STYLES to bars by facecolor encounter order, then set BW fills."""
    if not BW:
        return assign_hatches_color(patches), None
    hmap = {}
    idx = 0
    for bar in patches:
        fc = bar.get_facecolor()
        if fc not in hmap:
            style = BAR_STYLES[idx] if idx < len(BAR_STYLES) else ("white", HATCHES[idx % len(HATCHES)])
            hmap[fc] = style
            idx += 1
    for bar in patches:
        style = hmap[bar.get_facecolor()]
        bar.set_facecolor(style[0])
        bar.set_edgecolor("black")
        bar.set_hatch(style[1])
    if legend_handles:
        for h in legend_handles:
            fc = h.get_facecolor()
            if fc in hmap:
                style = hmap[fc]
                h.set_facecolor(style[0])
                h.set_edgecolor("black")
                h.set_hatch(style[1])
    return hmap


def assign_hatches_color(patches):
    """Original color-mode hatch assignment."""
    hmap = {}
    idx = 0
    for bar in patches:
        fc = bar.get_facecolor()
        if fc not in hmap:
            hmap[fc] = HATCHES[idx % len(HATCHES)]
            idx += 1
        bar.set_hatch(hmap[fc])
    return hmap


def hatch_legend(ax, hmap):
    for h in ax.get_legend().legend_handles:
        fc = h.get_facecolor()
        if fc in hmap:
            if BW:
                style = hmap[fc]
                h.set_facecolor(style[0])
                h.set_edgecolor("black")
                h.set_hatch(style[1])
            else:
                h.set_hatch(hmap[fc])


def style_legend(leg):
    if BW and leg is not None:
        leg.set_frame_on(False)
        for t in leg.get_texts():
            t.set_fontsize(8)


def savefig(fig, name, outdir):
    outpath = os.path.join(outdir, f"{name}{SUFFIX}.pdf")
    fig.savefig(outpath, bbox_inches="tight")
    if BW:
        pngpath = os.path.join(outdir, f"{name}{SUFFIX}.png")
        fig.savefig(pngpath, bbox_inches="tight", dpi=200)
        print(f"  Saved {outpath} + {pngpath}")
    else:
        print(f"  Saved {outpath}")


# -- Data loading ------------------------------------------------------------

def resolve_results_base():
    user = os.environ.get("USER", "nobody")
    share = f"/share/{user}"
    if os.path.isdir(share):
        return share
    script_dir = os.path.dirname(os.path.abspath(__file__))
    return os.path.join(script_dir, "..", "..", "results")


def load_model_checker(results_base):
    dfs = []
    for short, full in [("arm", "arm64"), ("x86", "x86_64")]:
        path = os.path.join(results_base, f"{short}.csv")
        if not os.path.exists(path):
            continue
        df = pd.read_csv(path)
        df["module_name"] = df["filename"].apply(lambda l: l.split("/")[0])
        df["entry"] = df["filename"].apply(lambda l: l.split("/")[1])
        df["arch"] = full
        dfs.append(df)
    return pd.concat(dfs, ignore_index=True) if dfs else pd.DataFrame()


def load_chains(results_base):
    all_chains = []
    for arch in ["arm64", "x86_64"]:
        pattern = os.path.join(results_base, "results", arch, "previous", "*", "Enhanced_Chains.csv")
        for path in glob.glob(pattern):
            try:
                df = pd.read_csv(path)
                if len(df) > 0:
                    df["arch"] = arch
                    all_chains.append(df)
            except Exception:
                continue
    return pd.concat(all_chains, ignore_index=True) if all_chains else pd.DataFrame()


def load_stats(results_base):
    lkmm_stats, times = [], []
    for arch in ["arm64", "x86_64"]:
        pattern = os.path.join(results_base, "results", arch, "previous", "*", "Stats.json")
        for path in glob.glob(pattern):
            try:
                with open(path) as f:
                    buf = json.load(f)
            except (json.JSONDecodeError, ValueError):
                continue
            clean = {k: v for k, v in buf.items() if "lkmm" in k}
            df = pd.DataFrame([clean])
            df["arch"] = arch
            lkmm_stats.append(df)
            for k, v in buf.items():
                if "time." in k:
                    _, kind, pas, clock = k.split(".")
                    times.append({"Kind": kind, "Pass": pas, "Clock": clock, "Time": v, "arch": arch})
    return (pd.concat(lkmm_stats, ignore_index=True),
            pd.DataFrame(times))


def add_zoom_polygon(fig, top_ax, bot_ax, top_patches, bot_patches, alpha=0.3):
    """Draw a shaded polygon connecting two bar regions across subplots."""
    tl = top_patches[0]
    tr = top_patches[-1]
    bl = bot_patches[0]
    br = bot_patches[-1]

    top_l = (tl.get_x(), tl.get_y() + tl.get_height())
    top_r = (tr.get_x() + tr.get_width(), tr.get_y() + tr.get_height())
    bot_l = (bl.get_x(), bl.get_y())
    bot_r = (br.get_x() + br.get_width(), br.get_y())

    lines = []
    for xy_a, xy_b, ax_a, ax_b in [(top_l, bot_l, top_ax, bot_ax),
                                     (top_r, bot_r, top_ax, bot_ax)]:
        cp = ConnectionPatch(xyA=xy_a, coordsA=ax_a.transData,
                             xyB=xy_b, coordsB=ax_b.transData)
        cp.set_color([0, 0, 0, 0])
        fig.add_artist(cp)
        lines.append(cp)

    coords = np.concatenate((lines[0].get_path().vertices,
                              lines[1].get_path().vertices[::-1]))
    col = tl.get_facecolor()
    if BW:
        col = (0.7, 0.7, 0.7, 1.0)
    fig.add_artist(plt.Polygon(coords, ec=None, fc=col, alpha=alpha,
                               zorder=100, clip_on=False, closed=False))


# -- Individual plots --------------------------------------------------------

def k_formatter(x, _pos):
    if x == 0:
        return "0"
    if x % 1000 == 0:
        return f"{int(x / 1000)}k"
    return f"{x / 1000:.1f}k"


def plot_percentage(df_matching, df_mc_stat, arch, sz, outdir):
    palette = get_palette()
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=sz["percentage"],
                                    gridspec_kw={"hspace": 1.5, "left": 0, "right": 0.9},
                                    sharex=True)
    if not BW:
        sns.set_context(sz["context"])
        sns.set(style="white", font="cmr10")

    df_preopt = df_matching[df_matching["Optimization Phase"] == "pre-opt"].copy()
    df_preopt["Dependencies"] = ["Preserved" if m else "Broken" for m in df_preopt["Matched"].values]

    sns.histplot(data=df_preopt, y="Optimization Phase", hue="Dependencies",
                 multiple="stack", stat="percent", ax=ax1, palette=palette,
                 edgecolor="black", hue_order=["Preserved", "Broken"], linewidth=0.5)
    ax1.set_ylabel("")
    ax1.set_title(" ")
    ax1.set_xlim(0, 101)

    tmp = df_mc_stat.sort_values(by=["result"])
    n_results = len(tmp["result"].unique())
    if BW:
        palette2_use = get_palette(n=n_results)
    else:
        palette2 = get_palette(n=n_results + 2)
        palette2_use = palette2[2:]
    sns.histplot(data=tmp, y="Analysis", hue="result", multiple="stack",
                 stat="percent", ax=ax2, palette=palette2_use,
                 edgecolor="black", linewidth=0.5)

    hmap = apply_bw_bars(ax1.patches + ax2.patches)

    ax2.set_ylabel("")
    ax2.set_title("")
    ax2.set_xlim(0, 101)
    ax2.set_xlabel("")
    ax2.set_xticks([0, 20, 40, 60, 80, 100], [f"{x}%" for x in [0, 20, 40, 60, 80, 100]])

    h = ax1.get_legend().legend_handles
    ax1.legend([h[1], h[0]], ["Preserved", "Broken"])
    sns.move_legend(ax1, "lower center", bbox_to_anchor=(0.5, 1), ncols=2,
                    title="Compiler-Based Analysis: Dependencies")
    sns.move_legend(ax2, "upper center", bbox_to_anchor=(0.5, -0.5), ncols=3,
                    title="Model Checking: Result")
    hatch_legend(ax1, hmap)
    hatch_legend(ax2, hmap)
    style_legend(ax1.get_legend())
    style_legend(ax2.get_legend())

    for ax in (ax1, ax2):
        ax.set_yticks([])
        ax.tick_params(axis="x", length=0)

    add_zoom_polygon(fig, ax1, ax2,
                     [ax1.patches[0], ax1.patches[1]],
                     [ax2.patches[0], ax2.patches[-1]], alpha=0.2)

    sns.despine(left=True, bottom=True)
    fig.tight_layout()
    savefig(fig, f"percentage-{arch}", outdir)
    plt.close(fig)


def plot_da_times(df_mc_stat, arch, sz, outdir):
    if BW:
        markers = ["o", "s", "^", "D", "v"]
        palette = ["black", "gray", "white"]
    else:
        palette = sns.color_palette("pastel")
        markers = True
    custom = {"axes.spines.right": True, "axes.spines.top": True}
    if not BW:
        sns.set_theme(style="ticks", rc=custom, font="cmr10")

    fig, ax = plt.subplots(1, 1, figsize=sz["da_times"])
    sns.scatterplot(x="time", y="events", hue="result", style="result",
                    data=df_mc_stat[df_mc_stat["Finished"]], palette=palette,
                    edgecolor="black", ax=ax, markers=markers)
    ax.set_title("")
    ax.set_xlabel("Model Checking time [s]")
    ax.set_ylabel("#Events")
    ax.yaxis.set_major_locator(ticker.MultipleLocator(1000))
    ax.yaxis.set_minor_locator(ticker.NullLocator())
    ax.yaxis.set_major_formatter(ticker.FuncFormatter(k_formatter))
    if ax.get_legend() is not None:
        sns.move_legend(ax, "lower center", bbox_to_anchor=(0.5, 1), ncols=3,
                        title="Model Checking: Result")
        style_legend(ax.get_legend())
    savefig(fig, f"da-times-{arch}", outdir)
    plt.close(fig)


def plot_dep_sources(df_deps, arch, sz, outdir):
    palette = get_palette(n=3)
    fig, axes = plt.subplots(1, 3, figsize=sz["dep_sources"])
    for i, dep_type in enumerate(DEP_ORDER):
        counts = (df_deps[df_deps["Dependency Type"] == dep_type]
                  .groupby("From").size().nlargest(6)
                  .to_frame(name="Count").reset_index(names="From"))
        sns.barplot(data=counts, y="From", x="Count", ax=axes[i],
                    color=palette[i], edgecolor="black")
        axes[i].set_title(DEP_TITLES[dep_type], fontsize=8 if BW else None)
        axes[i].set_xlabel("")
        axes[i].set_ylabel("")
        axes[i].xaxis.set_major_formatter(ticker.FuncFormatter(k_formatter))
    if BW:
        for i, dep_type in enumerate(DEP_ORDER):
            style = DEP_STYLES[dep_type]
            for bar in axes[i].patches:
                bar.set_facecolor(style[0])
                bar.set_edgecolor("black")
                bar.set_hatch(style[1])
    sns.despine()
    plt.tight_layout()
    savefig(fig, f"dep-sources-{arch}", outdir)
    plt.close(fig)


def plot_dep_sinks(df_deps, arch, sz, outdir):
    palette = get_palette(n=3)
    fig, axes = plt.subplots(1, 3, figsize=sz["dep_sinks"])
    for i, dep_type in enumerate(DEP_ORDER):
        counts = (df_deps[df_deps["Dependency Type"] == dep_type]
                  .groupby("To").size().nlargest(10)
                  .to_frame(name="Count").reset_index(names="To"))
        sns.barplot(data=counts, y="To", x="Count", ax=axes[i],
                    color=palette[i], edgecolor="black")
        axes[i].set_title(DEP_TITLES[dep_type], fontsize=8 if BW else None)
        axes[i].set_xlabel("")
        axes[i].set_ylabel("")
        axes[i].set_yticks([])
        axes[i].xaxis.set_major_formatter(ticker.FuncFormatter(k_formatter))
    axes[1].set_xlabel("Count")
    if BW:
        for i, dep_type in enumerate(DEP_ORDER):
            style = DEP_STYLES[dep_type]
            for bar in axes[i].patches:
                bar.set_facecolor(style[0])
                bar.set_edgecolor("black")
                bar.set_hatch(style[1])
    plt.tight_layout()
    savefig(fig, f"dep-sinks-{arch}", outdir)
    plt.close(fig)


def plot_dep_hist(df_deps, hmap, arch, sz, outdir):
    if not BW:
        custom = {"axes.spines.right": True, "axes.spines.top": True}
        sns.set_theme(style="ticks", rc=custom, font="cmr10")

    df_deps = df_deps.copy()
    df_deps["Dep"] = [DEP_SHORT[d] for d in df_deps["Dependency Type"].values]
    dep_short_order = [DEP_SHORT[d] for d in DEP_ORDER]
    palette = get_palette() if BW else "pastel"

    fig, axes = plt.subplots(1, 2, figsize=sz["dep_hist"], sharey=True)
    xlabs = ["Pre optimizations", "Post optimizations"]
    for i, opt in enumerate(["pre-opt", "post-opt"]):
        dat = df_deps[df_deps["Optimization Phase"] == opt]
        sns.histplot(data=dat, stat="count", ax=axes[i], edgecolor="black",
                     x="Dependency Type", hue="Dep", palette=palette,
                     hue_order=dep_short_order, multiple="stack")
        axes[i].set_xticks([])
        axes[i].set_xlabel(xlabs[i])
        axes[i].yaxis.set_major_formatter(ticker.FuncFormatter(k_formatter))

    if BW:
        # Build color→short-name map from the legend
        leg = axes[0].get_legend()
        color_to_dep = {}
        if leg:
            for h, t in zip(leg.legend_handles, leg.get_texts()):
                color_to_dep[h.get_facecolor()] = t.get_text()
        # Apply fixed DEP_STYLES by matching bar color → dep name → style
        for ax in axes:
            for bar in ax.patches:
                fc = bar.get_facecolor()
                dep_name = color_to_dep.get(fc)
                if dep_name and dep_name in DEP_STYLES:
                    style = DEP_STYLES[dep_name]
                    bar.set_facecolor(style[0])
                    bar.set_edgecolor("black")
                    bar.set_hatch(style[1])
        # Style legend handles
        if leg:
            for h in leg.legend_handles:
                fc = h.get_facecolor()
                dep_name = color_to_dep.get(fc)
                if dep_name and dep_name in DEP_STYLES:
                    style = DEP_STYLES[dep_name]
                    h.set_facecolor(style[0])
                    h.set_edgecolor("black")
                    h.set_hatch(style[1])
    else:
        for i in range(2):
            for bar in axes[i].patches:
                fc = bar.get_facecolor()
                if fc in hmap:
                    bar.set_hatch(hmap[fc])

    sns.move_legend(axes[0], "upper center", bbox_to_anchor=(0.5, 1), title="")
    axes[1].get_legend().remove()
    if not BW:
        for h in axes[0].get_legend().legend_handles:
            fc = h.get_facecolor()
            if fc in hmap:
                h.set_hatch(hmap[fc])
    style_legend(axes[0].get_legend())
    sns.despine()
    savefig(fig, f"dep-hist-{arch}", outdir)
    plt.close(fig)


def plot_sa_times(df_times, arch, sz, outdir):
    palette = get_palette()
    if BW:
        no_box = {"axes.spines.right": False, "axes.spines.top": False, "axes.spines.left": False}
        sns.set_style("ticks", {**no_box, "axes.grid": False})
    else:
        no_box = {"axes.spines.right": False, "axes.spines.top": False, "axes.spines.left": False}
        sns.set_theme(style="white", rc=no_box, font="cmr10")

    df_times = df_times.copy()
    df_times = df_times[df_times["Clock"] == "user"]
    df_times["LKMM"] = ["LKMM" in p for p in df_times["Pass"].values]
    df_times["Minutes"] = df_times["Time"] / 3600

    fig, (clang_ax, pa_ax, lk_ax) = plt.subplots(
        3, 1, figsize=sz["sa_times"],
        gridspec_kw={"hspace": 1, "left": 0.1}, sharex=False)

    # -- Clang breakdown --
    cl_df = df_times[df_times["Kind"] == "clang"]
    bars = []
    slices = []
    for p in ["frontend", "irgen", "optimizer"]:
        bars.append(cl_df[cl_df["Pass"] == p])
        s = pd.concat(bars, ignore_index=True)
        s["Pass"] = p
        slices.append(s)

    if BW:
        clang_palette = sns.color_palette("Greys", n_colors=3)
    else:
        clang_palette = sns.color_palette("pastel")
    for i, s in enumerate(slices[::-1]):
        pal = clang_palette[i:] if not BW else clang_palette[i:]
        sns.barplot(data=s, x="Minutes", hue="Pass", estimator=np.sum,
                    palette=pal, edgecolor="black", ax=clang_ax, errorbar=None)

    clang_ax.xaxis.tick_top()
    clang_ax.xaxis.set_label_position("top")
    clang_ax.tick_params(axis="x", length=0)
    clang_ax.set_xticks([])
    clang_ax.set_xlabel("")

    # -- Pass breakdown (LKMM vs regular) --
    pa_df = df_times[df_times["Kind"] == "pass"]
    bars = []
    slices = []
    for p in pa_df["LKMM"].unique():
        bars.append(pa_df[pa_df["LKMM"] == p])
        s = pd.concat(bars, ignore_index=True)
        s["LKMM"] = p
        slices.append(s)

    sum_passes = np.sum(slices[-1]["Minutes"].values)
    if BW:
        pa_palette = sns.color_palette("Greys", n_colors=5)
    else:
        pa_palette = sns.color_palette("pastel")
    for i, s in enumerate(slices[::-1]):
        s["Percentage"] = 100 * s["Minutes"] / sum_passes
        pal = pa_palette[3 + i:] if not BW else pa_palette[i:]
        sns.barplot(data=s, x="Percentage", hue="LKMM", estimator=np.sum,
                    palette=pal, edgecolor="black", ax=pa_ax, errorbar=None)

    pa_ax.set_xticks([])
    pa_ax.set_xlabel("")
    pa_ax.bar_label(pa_ax.containers[1], labels=["Regular opt"], padding=10)
    pa_ax.bar_label(pa_ax.containers[1], label_type="center", labels=["Compiler-based analysis"])
    pa_ax.get_legend().remove()

    # -- LKMM pass breakdown --
    lk_df = df_times[df_times["LKMM"]]
    bars = []
    slices = []
    for p in ["LKMMAnnotateHook", "LKMMAnnotateDepsPass", "LKMMVerifyDepsPass"]:
        bars.append(lk_df[lk_df["Pass"] == p])
        s = pd.concat(bars, ignore_index=True)
        s["Pass"] = p
        slices.append(s)

    sum_lk = np.sum(slices[-1]["Minutes"].values)
    if BW:
        lk_palette = sns.color_palette("Greys", n_colors=7)
    else:
        lk_palette = sns.color_palette("pastel")
    for i, s in enumerate(slices[::-1]):
        s["Percentage"] = 100 * s["Minutes"] / sum_lk
        s["Name"] = [LK_PASSES.get(x) for x in s["Pass"].values]
        pal = lk_palette[5 + i:] if not BW else lk_palette[i:]
        sns.barplot(data=s, x="Percentage", hue="Name", estimator=np.sum,
                    palette=pal, edgecolor="black", ax=lk_ax, errorbar=None)

    lk_ax.set_xticks([0, 20, 40, 60, 80, 100], [f"{x}%" for x in [0, 20, 40, 60, 80, 100]])
    lk_ax.set_xlabel("")
    lk_ax.tick_params(axis="x", pad=-3)

    # Zoom polygons
    add_zoom_polygon(fig, clang_ax, pa_ax,
                     [clang_ax.containers[1].patches[0], clang_ax.containers[0].patches[0]],
                     [pa_ax.containers[0].patches[0], pa_ax.containers[-1].patches[-1]])
    add_zoom_polygon(fig, pa_ax, lk_ax,
                     [pa_ax.containers[-1].patches[0]],
                     [lk_ax.containers[0].patches[0], lk_ax.containers[-1].patches[-1]])

    # Apply BW styling to bars
    all_patches = clang_ax.patches + lk_ax.patches
    hmap = apply_bw_bars(all_patches)

    # Legends
    h, l = clang_ax.get_legend_handles_labels()
    clang_ax.legend([h[2], h[1], h[0]], [l[2], l[1], l[0]])
    sns.move_legend(clang_ax, "lower center", bbox_to_anchor=(0.5, 0.98), ncols=3, title="Clang step")

    h, l = lk_ax.get_legend_handles_labels()
    lk_ax.legend([h[2], h[1], h[0]], [l[2], l[1], l[0]])
    sns.move_legend(lk_ax, "upper center", bbox_to_anchor=(0.5, -0.5), ncols=3,
                    title="Compiler-Based Analysis step")

    hatch_legend(clang_ax, hmap)
    hatch_legend(lk_ax, hmap)
    style_legend(clang_ax.get_legend())
    style_legend(lk_ax.get_legend())

    sns.despine(left=True, bottom=True)
    savefig(fig, f"sa-times-{arch}", outdir)
    plt.close(fig)


# -- Stats printout ----------------------------------------------------------

def print_stats(df_mc_stat, df_deps, df_times, arch):
    print(f"\n=== Statistics for {arch} ===")

    # Model checker result counts
    total = len(df_mc_stat)
    for r in df_mc_stat["result"].unique():
        n = len(df_mc_stat[df_mc_stat["result"] == r])
        print(f"  {r}: {n} ({100 * n / total:.1f}%)")

    # Median events
    finished = df_mc_stat[df_mc_stat["Finished"]]
    timeouts = df_mc_stat[df_mc_stat["result"] == "TIMEOUT"].dropna()
    if finished["events"].notna().any():
        print(f"  Median events (finished): {np.median(finished['events'].dropna().values):.0f}")
        if len(timeouts) and timeouts["events"].notna().any():
            print(f"  Median events (timeout):  {np.median(timeouts['events'].dropna().values):.0f}")

    # Pre/post opt counts
    for opt in ["pre-opt", "post-opt"]:
        n = len(df_deps[df_deps["Optimization Phase"] == opt])
        print(f"  {opt}: {n}")

    # Timing
    df_t = df_times.copy()
    df_t = df_t[df_t["Clock"] == "user"]
    df_t["LKMM"] = ["LKMM" in p for p in df_t["Pass"].values]
    df_t["Minutes"] = df_t["Time"] / 3600

    cl = df_t[df_t["Kind"] == "clang"]
    cl_total = np.sum(cl["Minutes"].values)
    cl_opt = np.sum(cl[cl["Pass"] == "optimizer"]["Minutes"].values)
    print(f"  Clang total: {cl_total:.1f}h; optimizer: {cl_opt:.1f}h ({100 * cl_opt / cl_total:.1f}%)")

    pa = df_t[df_t["Kind"] == "pass"]
    sa = np.sum(pa[pa["LKMM"]]["Minutes"].values)
    print(f"  Pass total: {np.sum(pa['Minutes'].values):.1f}h; SA: {sa:.1f}h")

    lk = df_t[df_t["LKMM"]]
    lk_total = np.sum(lk["Minutes"].values)
    for p in lk["Pass"].unique():
        t = np.sum(lk[lk["Pass"] == p]["Minutes"].values)
        print(f"    {p}: {100 * t / lk_total:.1f}%")


# -- Main --------------------------------------------------------------------

def main():
    global BW, SUFFIX

    parser = argparse.ArgumentParser(description="Generate DepSan analysis plots.")
    parser.add_argument("--mode", choices=["paper", "slide"], default="paper",
                        help="Plot sizing preset (default: paper)")
    parser.add_argument("--bw", action="store_true",
                        help="Generate black-and-white plots with -bw suffix")
    parser.add_argument("--arch", default="x86_64",
                        help="Architecture to plot (default: x86_64)")
    parser.add_argument("--outdir", default=".",
                        help="Output directory for PDFs (default: .)")
    parser.add_argument("--results", default=None,
                        help="Results base directory (default: auto-detect)")
    args = parser.parse_args()

    BW = args.bw
    SUFFIX = "-bw" if BW else ""

    if BW:
        sz = PAPER_BW
    elif args.mode == "paper":
        sz = PAPER
    else:
        sz = SLIDE

    setup_style(sz)

    results_base = args.results or resolve_results_base()
    outdir = args.outdir
    arch = args.arch
    os.makedirs(outdir, exist_ok=True)

    print(f"Loading data from {results_base} ...")
    df_mc = load_model_checker(results_base)
    df_deps = load_chains(results_base)
    df_stats, df_times = load_stats(results_base)

    # Filter to requested arch
    df_deps = df_deps[df_deps["arch"] == arch] if "arch" in df_deps.columns else df_deps
    df_stats = df_stats[df_stats["arch"] == arch] if len(df_stats) else df_stats
    df_times = df_times[df_times["arch"] == arch] if len(df_times) else df_times

    has_mc = len(df_mc) > 0
    if has_mc:
        df_mc = df_mc[df_mc["arch"] == arch]

    # Prepare matching / mc_stat subsets
    tmp = df_deps[(df_deps["Optimization Phase"] == "pre-opt") &
                  (df_deps["Matched"].isin([True, False]))]
    df_matching = tmp.copy()

    if has_mc:
        stat_mods = tmp[tmp["Matched"]]["Module"].unique()
        df_mc_stat = df_mc[df_mc["module_name"].isin(stat_mods)].copy()
        df_mc_stat["Analysis"] = "dynamic"
        df_mc_stat["Finished"] = df_mc_stat["result"].isin(FINISHED_RESULTS)

    mode_label = "bw" if BW else args.mode
    print(f"Generating {mode_label} plots for {arch} ...")

    # Build hatch map from palette (used in color mode for dep_hist)
    past = sns.color_palette("pastel")
    hmap = {}
    idx = 0
    for c in past[:6]:
        hmap[tuple(c)] = HATCHES[idx % len(HATCHES)]
        idx += 1

    if has_mc:
        plot_percentage(df_matching, df_mc_stat, arch, sz, outdir)

        if df_mc_stat["events"].notna().any():
            plot_da_times(df_mc_stat, arch, sz, outdir)
        else:
            print("  skipping da-times (no event counts in model checker data)")
    else:
        print("  skipping percentage, da-times (no model checker data)")

    if len(df_deps):
        plot_dep_sources(df_deps, arch, sz, outdir)
        plot_dep_sinks(df_deps, arch, sz, outdir)
        plot_dep_hist(df_deps, hmap, arch, sz, outdir)

    if len(df_times):
        plot_sa_times(df_times, arch, sz, outdir)

    if has_mc:
        print_stats(df_mc_stat, df_deps, df_times, arch)

    print(f"\nDone. PDFs written to {os.path.abspath(outdir)}")


if __name__ == "__main__":
    main()
