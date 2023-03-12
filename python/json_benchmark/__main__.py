from json_benchmark import app
from json_benchmark.cli import parse_args

if __name__ == '__main__':
    args = parse_args()
    app.run(args.num_objects, args.num_runs, args.csv_file)
