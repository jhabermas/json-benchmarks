import os
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from json_benchmark.cli import parse_args
from subprocess import run


def benchmark_commands(num_json_objects, num_runs, results_folder):
    n = str(num_json_objects)
    r = str(num_runs)
    return [
        {
            "name":"python",
            "command": ["python", "-m", "json_benchmark", "--num-objects", n, "--num-runs", r, "--csv-file", os.path.join(results_folder, "python.csv")]
        },
        {
            "name":"c++",
            "command": [os.path.join("bin", "jsb"), "-n", n, "-r", r, "-o", os.path.join(results_folder, "cpp.csv")]
        },
        {
            "name":"node",
            "command": ["node", os.path.join("node", "main.js"), n, r, os.path.join(results_folder, "node.csv")]
        },
        {
            "name":"rust",
            "command": ["cargo", "run", "--release", n, r, os.path.join(results_folder, "rust.csv")]
        }
    ]


def run_benchmarks(commands, dry_run=False):
    output_files = []
    for cmd in commands:
        print(f"Running {cmd['name']} benchmark")
        if not dry_run:
            run(cmd["command"])
        output_files.append(cmd["command"][-1])
    return output_files


def gather_results(output_files):
    results = [pd.read_csv(file).T.reset_index() for file in output_files]
    df = pd.DataFrame(columns=['Benchmark', 'Time'])
    for benchmark in results:
        benchmark.columns = ['Benchmark', 'Time']
        df = pd.concat([df, benchmark])
    return df


def show_results(df, output_folder, num_objects):
    fig, ax = plt.subplots(figsize=(8, 6))
    bars = ax.barh(df['Benchmark'], df['Time'], color=plt.cm.Dark2(range(1, len(df))))
    fig.subplots_adjust(left=0.2)
    
    ax.bar_label(bars, fmt='{:,.1f} ms', label_type='center', fontsize=8)
    ax.set_xlabel('Time (ms)')
    ax.set_ylabel('Benchmark')
    ax.set_title(f'Round-trip transform {num_objects} JSON objects')
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.set_xlim([0.0, df['Time'].max() * 1.2])

    #plt.tight_layout()
    plt.savefig('benchmark_results.png')
    plt.show()


if __name__ == '__main__':
    args = parse_args()
    results_dir = os.path.abspath(args.csv_file)
    os.makedirs(results_dir, exist_ok=True)
    benchmarks = benchmark_commands(args.num_objects, args.num_runs, results_dir)
    outputs = run_benchmarks(benchmarks)
    results = gather_results(outputs)
    show_results(results, results_dir, args.num_objects)
