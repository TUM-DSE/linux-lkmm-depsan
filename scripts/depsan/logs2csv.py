import os
import re
import csv
import argparse

# regex patterns
program_pattern = re.compile(r"(?:Program path|Test):\s*(.*)")
result_pattern = re.compile(r"Result:\s*(\w+)")
time_pattern = re.compile(r"Time:\s*([\d.]+)\s*secs")

events_pattern = re.compile(r"#Events:\s*(\d+)")
loads_pattern = re.compile(r"#Loads:\s*(\d+)")
stores_pattern = re.compile(r"#Stores:\s*(\d+)")
loops_pattern = re.compile(r"Detected\s+(\d+)\s+loops")

PREFIXES = ["/arm64/latest", "/x86_64/latest", "/arm64/", "/x86_64/"]

def extract_relative_path(full_path):
    rel = full_path
    for prefix in PREFIXES:
        if prefix in full_path:
            rel = full_path.split(prefix, 1)[1].lstrip("/")
            break

    if rel.endswith("Mod2.ll"):
        rel = rel[:-len("Mod2.ll")]

    return rel.rstrip("/")


def process_logs(log_dir, output_csv):
    rows = []

    for root, _, files in os.walk(log_dir):
        for file in files:
            filepath = os.path.join(root, file)

            program = None
            result = "TIMEOUT"
            time_val = 60.0

            events = None
            loads = None
            stores = None
            loops = None

            with open(filepath, "r", errors="ignore") as f:
                for line in f:
                    if program is None:
                        m = program_pattern.search(line)
                        if m:
                            program = extract_relative_path(m.group(1))

                    m = result_pattern.search(line)
                    if m:
                        result = m.group(1)

                    m = time_pattern.search(line)
                    if m:
                        time_val = float(m.group(1))

                    m = events_pattern.search(line)
                    if m:
                        events = int(m.group(1))

                    m = loads_pattern.search(line)
                    if m:
                        loads = int(m.group(1))

                    m = stores_pattern.search(line)
                    if m:
                        stores = int(m.group(1))

                    m = loops_pattern.search(line)
                    if m:
                        loops = int(m.group(1))

            if program is not None:
                rows.append([program, result, time_val, events, loads, stores, loops])

    with open(output_csv, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["filename", "result", "time", "events", "loads", "stores", "loops"])
        writer.writerows(rows)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Parse log files into CSV.")
    parser.add_argument("log_dir", help="Path to directory containing logs")
    parser.add_argument("output_csv", help="Output CSV file")

    args = parser.parse_args()

    process_logs(args.log_dir, args.output_csv)

    print(f"CSV written to {args.output_csv}")
