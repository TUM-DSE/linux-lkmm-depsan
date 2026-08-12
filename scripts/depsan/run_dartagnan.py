import os
import sys
import subprocess
import shutil
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path


def load_skip_list(path):
    skip = set()
    with path.open() as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue

            # normalize path-like entries to just the directory name
            name = Path(line).name
            skip.add(name)

    return skip


def run_dartagnan(cmd, output_path):
    with output_path.open("w") as f:
        subprocess.run(cmd, stdout=f, stderr=subprocess.STDOUT, check=False)


def main():
    if len(sys.argv) != 5:
        print(f"Usage: {sys.argv[0]} <root-folder> <cat-file> <skip-file> <output-dir>")
        sys.exit(1)

    root = Path(sys.argv[1])
    if not root.is_dir():
        print(f"Error: {root} is not a directory")
        sys.exit(1)

    cat_file = Path(sys.argv[2])
    if not cat_file.is_file():
        print(f"Error: {cat_file} is not a valid file")
        sys.exit(1)

    skip_file = Path(sys.argv[3])
    if not skip_file.is_file():
        print(f"Error: {skip_file} is not a valid file")
        sys.exit(1)

    output_dir = Path(sys.argv[4])

    skip_dirs = load_skip_list(skip_file)
    print(f"Skipping {len(skip_dirs)} directories")

    dartagnan = shutil.which("dartagnan")
    if not dartagnan:
        print("Error: dartagnan not found in PATH")
        sys.exit(1)

    required_file = "Mod2.ll"

    output_dir.mkdir(parents=True, exist_ok=True)
    print(f"Output directory: {output_dir}")

    # Collect all jobs, printing skip messages immediately
    jobs = []
    for outer in sorted(root.iterdir()):
        if not outer.is_dir():
            continue

        if outer.stem in skip_dirs:
            print(f"Skipping {outer.name}")
            continue

        for inner in sorted(outer.iterdir()):
            if not inner.is_dir():
                continue

            folder_name = inner.name
            file_path = inner / required_file
            output_path = output_dir / f"{folder_name}.out"

            if not file_path.is_file():
                print(f"Skipping {outer.name}/{folder_name}. {required_file} not found")
                continue

            cmd = [
                "timeout", "60",
                dartagnan,
                "-DlogLevel=info",
                str(cat_file),
                "--target=lkmm",
                "--solver=z3",
                "--method=eager",
                "--property=cat_spec",
                "--printer.afterProcessing=true",
                str(file_path),
                f"--entry={folder_name}",
                "--witness=png",
                "--witness.show=po,",
                f"--witness.filename={folder_name}",
                "--program.processing.skipAssertionsOfType=UNKNOWN_FUNCTION",
            ]

            jobs.append((f"{outer.name}/{folder_name}", cmd, output_path))

    print(f"Running {len(jobs)} dartagnan jobs with {os.cpu_count()} workers")

    # Run in parallel, print logs in submission order
    completed = {}
    next_idx = 0

    with ThreadPoolExecutor(max_workers=os.cpu_count()) as pool:
        future_to_idx = {}
        for idx, (display_name, cmd, output_path) in enumerate(jobs):
            future = pool.submit(run_dartagnan, cmd, output_path)
            future_to_idx[future] = idx

        for future in as_completed(future_to_idx):
            idx = future_to_idx[future]
            completed[idx] = True

            # Flush all consecutive completed jobs from next_idx
            while next_idx in completed:
                print(f"Running {jobs[next_idx][0]}")
                next_idx += 1


if __name__ == "__main__":
    main()
