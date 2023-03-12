import json
from json_benchmark.impl import transform


def transform_json(json_str):
    data = json.loads(json_str)
    new_data = transform(data)
    new_json_str = json.dumps(new_data)
    return new_json_str
