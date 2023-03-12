import csv
import timeit
from typing import List
from json_benchmark.impl import generate_json, python_json, rapidjson, orjson


def transform_all(transform_json_fn, json_data):
    transformed = []
    for item in json_data:
        transform_json_fn(item)


def benchmark_transform_json(transform_json_fn, json_data, num_runs):
    impl = transform_json_fn.__module__.split('.')[-1]
    print(f'Benchmarking {impl} using {len(json_data)} objects over {num_runs} runs...')
    return timeit.timeit(lambda: transform_all(transform_json_fn, json_data), number=num_runs) * 1000


def benchmark_all_transform_json(json_data, num_runs):
    orjson_time = benchmark_transform_json(orjson.transform_json, json_data, num_runs)
    python_time = benchmark_transform_json(python_json.transform_json, json_data, num_runs)
    rapidjson_time = benchmark_transform_json(rapidjson.transform_json, json_data, num_runs)
    return [python_time, orjson_time, rapidjson_time]


def write_results_to_csv(result_rows: List[List[float]], filename: str):
    with open(filename, mode='w') as csv_file:
        writer = csv.writer(csv_file)
        writer.writerow(['python_json', 'orjson', 'python-rapidjson'])
        for row in result_rows:
            writer.writerow(row)


def run(num_objects=100000, num_runs=3, csv_file='benchmark_results.csv'):
    json_data = generate_json(num_objects)
    result_rows = []
    result_row = benchmark_all_transform_json(json_data, num_runs)
    result_rows.append(result_row)
    write_results_to_csv(result_rows, csv_file)


if __name__ == '__main__':
    run()
