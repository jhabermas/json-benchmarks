import argparse


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('--num-objects', type=int, default=100000, help='Number of JSON objects to generate')
    parser.add_argument('--num-runs', type=int, default=3, help='Number of times to run the benchmark')
    parser.add_argument('--csv-file', type=str, default='benchmark_results.csv', help='Name of CSV file to save results')
    return parser.parse_args()
