import json
import random
import time
import uuid
from datetime import datetime


def generate_json(n):
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


def transform(data: dict):
    return {
        "id": data["id"][-8:],
        "str": data["string"].split()[0],
        "num": data["number"] + 1,
        "val": 0 if data["null"] is None else 1,
        "sum": sum(data["array"]),
        "obj": "object",
        "timestamp": datetime.utcfromtimestamp(data["timestamp"]).isoformat(timespec='seconds')
    }