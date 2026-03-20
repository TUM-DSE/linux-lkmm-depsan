#!/usr/bin/env python3
"""
Enhanced CSV generator for dependency chain analysis with matching information
Extends the original toCSV.py to include a 'Matched' column based on matched_chains.txt
"""

import pandas as pd
import os
import sys
import platform
import re
from pathlib import Path

arch = platform.machine()

segment_types = {
    "Intact": "< 0, 0>",
    "Rising": "<-1, 0>",
    "MayDangle": "<+1, 0>",
    "Dangling": "< 0,-1>",
    "RisingDangling": "<-1,-1>",
    "MayDangleDangling": "<+1,-1>",
    "MayRise": "< 0,+1>",
    "MayRiseRising": "<-1,+1>",
    "MayRiseMayDangle": "<+1,+1>",
    "Combined": "Combined"
}

base_dir = f"results/{arch}/latest"

def parse_matched_chains(matched_chains_file):
    if not os.path.exists(matched_chains_file):
        assert(False, f"Error: matched_chains.txt not found in {matched_chains_file}")

    try:
        with open(matched_chains_file, 'r', errors='ignore') as f:
            content = f.read()
        df = pd.DataFrame(columns=["ID", "Status", "Matched with"])
        in_chain = False
        matching = False
        seen_pre_opt = False
        pre_id = None
        seen_post_opt = False
        post_id = None

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
                        df.loc[len(df)] = [pre_id, "Matched", num]
                    else:
                        pre_id = num
                        seen_pre_opt = True
                else:
                    df.loc[len(df)] = [num, "Missing", None]
            if line.strip() == "":
                in_chain = False
                matching = False
                seen_pre_opt = False
                pre_id = None
                seen_post_opt = False
                post_id = None

    except Exception as e:
        print(f"Warning: Could not parse {matched_chains_file}: {e}")

    return df


def parse_chains_enhanced(fd, phase, has_complete, dfIn, module_name, matched_chains):
    """Enhanced chain parser for both PRE-OPT and POST-OPT phases"""
    headers = ["Address Dependency", "Data Dependency", "Control Dependency"]
    current_type = ""
    current_seg = ""
    current_chain_id = None
    in_seg = False
    in_combined = False
    beg = ""
    end = ""

    for line in fd:
        line = line.strip()

        # Detect section headers
        if "~" in line:
            in_combined = False  # Reset when entering new dependency type
            for h in headers:
                if h in line:
                    current_type = h
                    break

        # Detect segment types and Combined sections
        if "Combined:" in line:
            current_seg = "Combined"
            in_combined = True
            continue

        # Handle Combined section specially
        if in_combined:
            chain_match = re.match(r'^(\d{10,})', line)
            if chain_match:
                current_chain_id = line.split(":")[0].strip()
                continue

        if in_combined:
            if "|" in line:
                tmp = line.split("/")[-1].split(":")[0]
                if in_seg:
                    end = tmp
                else:
                    beg = tmp
                    in_seg = True

            if len(line) == 0:
                is_matched = None
                if phase == "pre-opt":
                    # PRE-OPT chains: check if matched or missing
                    is_matched = matched_chains[matched_chains["ID"] == current_chain_id]["Status"].values[0] == "Matched"
                elif phase == "post-opt":
                    is_matched = not matched_chains[matched_chains["Matched with"] == current_chain_id].empty

                current_chain_id = None
                in_seg = False
                new_row = {
                    "Module": module_name,
                    "Empty": has_complete,
                    "Segment Type": current_seg,
                    "Dependency Type": current_type,
                    "Optimization Phase": phase,
                    "From": beg,
                    "To": end,
                    "Matched": is_matched,
                    "Chain ID": current_chain_id,
                    "Matchable": True
                }
                dfIn.loc[len(dfIn)] = new_row

                beg = ""
                end = ""


def main():
    # Check if base directory exists
    if not os.path.exists(base_dir):
        print(f"Error: Base directory {base_dir} not found")
        sys.exit(1)
    # Read NON-EMPTY file
    non_empty_file = os.path.join(base_dir, "NON-EMPTY")
    if os.path.exists(non_empty_file):
        with open(non_empty_file, "r") as ne:
            buf = ne.read()
    else:
        assert(False, f"Error: NON-EMPTY file not found in {base_dir}")
    # Process all module directories
    module_desc = []
    for f in os.scandir(base_dir):
        if f.is_dir() and f.name != "plots":
            module_desc.append((f.path, f.name, f.name in buf))

    processed_count = 0
    for module_dir, module_name, has_complete in module_desc:
        #if module_name != "mm-ksm":
        #    continue
        output_csv = os.path.join(module_dir, "Enhanced_Chains.csv")

        # Skip if enhanced CSV already exists
        #if os.path.exists(output_csv):
        #    print(f"Enhanced CSV already exists for {module_name}, skipping...")
        #    continue

        # Check for segment files
        pre_segments_file = os.path.join(module_dir, "Pre_Segments.txt")
        post_segments_file = os.path.join(module_dir, "Post_Segments_.txt")  # Note the underscore

        if not os.path.exists(pre_segments_file):
            print(f"Warning: {pre_segments_file} not found, skipping {module_name}")
            continue

        # Parse matched chains information (shows which PRE-OPT chains matched to POST-OPT)
        matched_chains_file = os.path.join(module_dir, "matched_chains.txt")
        matched_chains = parse_matched_chains(matched_chains_file)

        print(f"Processing {module_name}...")
        # Create enhanced dataframe
        dfC = pd.DataFrame(columns=[
            "Module", "Empty", "Segment Type", "Dependency Type", 
            "Optimization Phase", "From", "To", "Matched", "Chain ID", "Matchable"
        ])
        # Parse PRE-OPT segments
        try:
            with open(pre_segments_file, 'r') as f:
                parse_chains_enhanced(f, "pre-opt", has_complete, dfC, module_name,
                                    matched_chains)

            # Parse POST-OPT segments if file exists
            if os.path.exists(post_segments_file):
                with open(post_segments_file, 'r') as f:
                    # POST-OPT chains: pass matched_post_chains to mark which were used
                    parse_chains_enhanced(f, "post-opt", has_complete, dfC, module_name,
                                        matched_chains)
            # Save enhanced CSV
            dfC.to_csv(output_csv, index=False)
            processed_count += 1
            print(f"  Saved enhanced CSV with {len(dfC)} entries")
        except Exception as e:
            print(f"Error processing {module_name}: {e}")
    print(f"\nProcessing complete! Enhanced CSV files created for {processed_count} modules.")
    print(f"Enhanced CSV files saved as 'Enhanced_Chains.csv' with corrected Combined chain matching.")
    print(f"Columns: Matched (True/False/None), Chain ID, Matchable (True/False), Optimization Phase (pre-opt/post-opt)")
    print(f"Logic: PRE-OPT Combined chains matched to POST-OPT chains via matched_chains.txt")

if __name__ == "__main__":
    main()
