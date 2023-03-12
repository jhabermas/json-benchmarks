import rapidjson as rjs
from json_benchmark.impl import transform


def transform_json(json_str):
    data = rjs.loads(json_str)
    new_data = transform(data)
    new_json_str = rjs.dumps(new_data)
    return new_json_str
