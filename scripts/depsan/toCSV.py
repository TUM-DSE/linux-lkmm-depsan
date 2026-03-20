import numpy as np
import pandas as pd
import seaborn as sns
import os
import sys
from datetime import datetime
import argparse
import json
import platform
import matplotlib.pyplot as plt
import re

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

def parse_chains(fd, phase, has_complete, dfIn, module_name):
    headers = ["Address Dependency", "Data Dependency", "Control Dependency"]
    current_type = ""
    current_seg = ""
    in_seg = False
    beg = ""
    end = ""
    for l in fd:
        #print(l)
        if "~" in l:
            #print("header\n")
            for h in headers:
                if h in l:
                    current_type = h
        if ": " in l:
            #print("Type")
            for t in segment_types.keys():
                if t in l:
                    current_seg = t
        if "Combined:" in l:
            #print("comb")
            current_seg = "Combined"

        if not in_seg and "|" in l:
            #print("start")
            in_seg = True
            beg = l.split("/")[-1].split(":")[0]
        if in_seg and len(l) == 1:
            #print("end")
            in_seg = False
            new_row = {
                        "Module": module_name,
                        "Empty": has_complete,
                        "Segment Type": current_seg,
                        "Dependency Type": current_type,
                        "Optimization Phase": phase,
                        "From": beg,
                        "To": end
                    }
            dfIn.loc[len(dfIn)] = new_row

            beg = ""
            end = ""
        if in_seg:
            #print(f"middle {len(l)}")
            end = l.split("/")[-1].split(":")[0]

with open(base_dir + "/NON-EMPTY", "r") as ne:
    buf = ne.read()
    module_desc = [(f.path, f.name, f.name in buf) for f in os.scandir(base_dir) if (f.is_dir() and f.name != "plots")]

for module_dir, module_name, has_complete in module_desc:
    # check if a dumped dataframe exists in the output directory
    if os.path.exists(os.path.join(module_dir, "Chains.csv")):
        #print("Found existing dataframes, loading...")
        pass
    else:
        dfC = pd.DataFrame(columns=["Module", "Empty", "Segment Type", "Dependency Type", "Optimization Phase","From", "To"])
        file_path = os.path.join(module_dir, "Pre_Segments.txt")
        print(f"Parsing {file_path}...")
        with open(file_path, 'r') as f:
            parse_chains(f, "pre-opt", has_complete, dfC, module_name)

        dfC.to_csv(os.path.join(module_dir, "Chains.csv"), index=False)
