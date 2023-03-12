import json
import time
from datetime import datetime
import pytest
from json_benchmark.impl import transform

TIMESPEC = 'seconds'


@pytest.mark.parametrize("input_json_str, expected_json_str", [
    (f'{{"id": "0123456789abcdef", "string": "hello world", "number": 42, "boolean": true, "null": null, "array": [1, 2, 3], "object": {{"foo": "bar"}}, "timestamp": {int(time.time())}}}',
     f'{{"id": "89abcdef", "str": "hello", "num": 43, "val": 0, "sum": 6, "obj": "object", "timestamp": "{datetime.now().isoformat(timespec=TIMESPEC)}"}}')
])
def test_transform(input_json_str, expected_json_str):
    expected_json = json.loads(expected_json_str)
    input_json = json.loads(input_json_str)
    result_json = transform(input_json)

    assert result_json == expected_json
