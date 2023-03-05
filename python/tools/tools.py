from enum import Enum
import json
import random
import time
import uuid


class JsonModule(Enum):
    JSON = 1,
    ORJSON = 2,
    RAPIDJSON = 3


def import_json_module(m):
    if m == JsonModule.ORJSON:
        import orjson as json
        print("Using orjson")
    elif m == JsonModule.RAPIDJSON:
        import rapidjson as json
        print("Using rapid json")
    else:
        import json
        print("Using build in json")


def generate_json_objects(n):
    json_array = []
    for i in range(n):
        obj = {
            "id": str(uuid.uuid4()),
            "string": "hello world",
            "number": random.randint(-100, 100),
            "boolean": random.choice([True, False]),
            "null": None,
            "array": [1, 2, 3, 4, 5, 6, 7, i],
            "object": {"key": i},
            "timestamp": int(time.time())
        }
        json_array.append(json.dumps(obj))
    return json_array