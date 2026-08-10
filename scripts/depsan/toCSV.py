#!/usr/bin/env python3
"""CSV generator for dependency chain analysis with matching information."""

import os
import sys
import platform
import re
import pandas as pd

COLUMNS = ["Module", "Empty", "Segment Type", "Dependency Type",
           "Optimization Phase", "From", "To", "Matched", "Chain ID", "Matchable"]

DEP_HEADERS = {"Address Dependency", "Data Dependency", "Control Dependency"}


def resolve_base_dir():
    outdir = os.environ.get("LKMM_OUTDIR")
    if outdir and os.path.isdir(outdir):
        return outdir

    arch = platform.machine()
    if arch == "aarch64":
        arch = "arm64"

    user = os.environ.get("USER", "nobody")
    share_dir = f"/share/{user}"
    if os.path.isdir(share_dir):
        return os.path.join(share_dir, "results", arch, "latest")

    script_dir = os.path.dirname(os.path.abspath(__file__))
    return os.path.join(script_dir, "..", "..", "results", arch, "latest")


def parse_matched_chains(path):
    if not os.path.exists(path):
        raise FileNotFoundError(f"matched_chains.txt not found: {path}")

    with open(path, 'r', errors='ignore') as f:
        content = f.read()

    rows = []
    in_chain = False
    matching = False
    seen_pre_opt = False
    pre_id = None

    for line in content.splitlines():
        if not in_chain and "Matched:" in line:
            in_chain = True
            matching = True
            continue
        if not in_chain and "Missing chain for" in line:
            in_chain = True
            matching = False
            continue
        if in_chain and "Dependency:" in line:
            num = line.split(": ")[-1].split(":")[0].strip()
            if matching:
                if seen_pre_opt:
                    rows.append({"ID": pre_id, "Status": "Matched", "Matched with": num})
                else:
                    pre_id = num
                    seen_pre_opt = True
            else:
                rows.append({"ID": num, "Status": "Missing", "Matched with": None})
        if line.strip() == "":
            in_chain = False
            matching = False
            seen_pre_opt = False
            pre_id = None

    return pd.DataFrame(rows, columns=["ID", "Status", "Matched with"])


def parse_chains(fd, phase, has_complete, module_name, matched_chains):
    """Parse Combined dependency chains from a segments file."""
    rows = []
    current_type = ""
    chain_id = None
    in_seg = False
    in_combined = False
    beg = ""
    end = ""

    for line in fd:
        line = line.strip()

        if "~" in line:
            in_combined = False
            for h in DEP_HEADERS:
                if h in line:
                    current_type = h
                    break

        if "Combined:" in line:
            in_combined = True
            continue

        if not in_combined:
            continue

        if re.match(r'^\d{10,}', line):
            chain_id = line.split(":")[0].strip()
            continue

        if "|" in line:
            name = line.split("/")[-1].split(":")[0]
            if in_seg:
                end = name
            else:
                beg = name
                in_seg = True

        if len(line) == 0 and in_seg:
            if phase == "pre-opt":
                match = matched_chains[matched_chains["ID"] == chain_id]
                is_matched = match.iloc[0]["Status"] == "Matched" if len(match) else None
            else:
                is_matched = not matched_chains[matched_chains["Matched with"] == chain_id].empty

            rows.append({
                "Module": module_name,
                "Empty": has_complete,
                "Segment Type": "Combined",
                "Dependency Type": current_type,
                "Optimization Phase": phase,
                "From": beg,
                "To": end,
                "Matched": is_matched,
                "Chain ID": chain_id,
                "Matchable": True,
            })
            chain_id = None
            in_seg = False
            beg = ""
            end = ""

    return rows


def main():
    base_dir = resolve_base_dir()
    if not os.path.isdir(base_dir):
        print(f"Error: Base directory {base_dir} not found")
        sys.exit(1)

    non_empty_file = os.path.join(base_dir, "NON-EMPTY")
    if not os.path.exists(non_empty_file):
        print(f"Error: NON-EMPTY file not found in {base_dir}")
        sys.exit(1)

    with open(non_empty_file, "r") as f:
        non_empty_buf = f.read()

    module_dirs = [
        (e.path, e.name, e.name in non_empty_buf)
        for e in os.scandir(base_dir)
        if e.is_dir() and e.name != "plots"
    ]

    processed = 0
    for module_dir, module_name, has_complete in module_dirs:
        pre_file = os.path.join(module_dir, "Pre_Segments.txt")
        post_file = os.path.join(module_dir, "Post_Segments_.txt")
        matched_file = os.path.join(module_dir, "matched_chains.txt")
        output_csv = os.path.join(module_dir, "Chains.csv")

        if not os.path.exists(pre_file):
            print(f"Warning: {pre_file} not found, skipping {module_name}")
            continue

        matched = parse_matched_chains(matched_file)

        print(f"Processing {module_name}...")
        try:
            rows = []
            with open(pre_file, 'r') as f:
                rows.extend(parse_chains(f, "pre-opt", has_complete, module_name, matched))

            if os.path.exists(post_file):
                with open(post_file, 'r') as f:
                    rows.extend(parse_chains(f, "post-opt", has_complete, module_name, matched))

            pd.DataFrame(rows, columns=COLUMNS).to_csv(output_csv, index=False)
            processed += 1
            print(f"  Saved {len(rows)} entries")
        except Exception as e:
            print(f"Error processing {module_name}: {e}")

    print(f"\nDone: {processed} modules processed.")


if __name__ == "__main__":
    main()
