const assert = require('assert');
const { transformJson } = require('./transform_json');

describe('transformJson', () => {
  it('should transform a json object according to specifications', () => {
    const inputJson = '{"id": "ac130003", "string": "hello world", "number": 10, "null": null, "array": [1,2,3], "timestamp": 1645489387}';
    const expectedJson = '{"id":"ac130003","str":"hello","num":11,"val":0,"sum":6,"obj":"object","timestamp":"2022-02-22T00:23:07.000Z"}';

    assert.strictEqual(transformJson(inputJson), expectedJson);
  });
});
