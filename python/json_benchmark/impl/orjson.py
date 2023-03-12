import orjson as orjs
from json_benchmark.impl import transform


def transform_json(json_str):
    data = orjs.loads(json_str)
    new_data = transform(data)
    new_json_str = orjs.dumps(new_data)
    return new_json_str
