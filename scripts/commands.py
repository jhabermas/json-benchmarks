from os import path

def benchmark_commands(num_json_objects, num_runs, results_folder):
    n = str(num_json_objects)
    r = str(num_runs)
    return [
        {
            "name":"python",
            "command": ["python", "-m", "json_benchmark", "--num-objects", n, "--num-runs", r, "--csv-file", path.join(results_folder, "python.csv")]
        },
        {
            "name":"c++",
            "command": [path.join("bin", "jsb"), "-n", n, "-r", r, "-o", path.join(results_folder, "cpp.csv")]
        },
        {
            "name":"node",
            "command": ["node", path.join("node", "main.js"), n, r, path.join(results_folder, "node.csv")]
        },
        {
            "name":"rust",
            "command": ["cargo", "run", "--release", n, r, path.join(results_folder, "rust.csv")]
        }
    ]
