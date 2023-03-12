const { v4: uuidv4 } = require('uuid');

function generateJsonArray(n) {
    const json_array = [];
    for (let i = 0; i < n; i++) {
        const obj = {
            id: uuidv4(),
            string: "hello world",
            number: Math.floor(Math.random() * 201) - 100,
            boolean: Math.random() < 0.5,
            null: null,
            array: [1, 2, 3, 4, 5, 6, 7, i],
            object: { key: i },
            timestamp: Math.floor(Date.now() / 1000)
        };
        const json_str = JSON.stringify(obj);
        json_array.push(json_str);
    }
    return json_array;
}

const transformJson = (jsonStr) => {
    const data = JSON.parse(jsonStr);
  
    const new_data = {
      id: data.id.slice(-8),
      str: data.string.split(" ")[0],
      num: data.number + 1,
      val: data.null === null ? 0 : 1,
      sum: data.array.reduce((acc, curr) => acc + curr, 0),
      obj: "object",
      timestamp: new Date(data.timestamp * 1000).toISOString(),
    };
  
    return JSON.stringify({
      id: new_data.id,
      str: new_data.str,
      num: new_data.num,
      val: new_data.val,
      sum: new_data.sum,
      obj: new_data.obj,
      timestamp: new_data.timestamp,
    });
  };
  
  module.exports = {
    generateJsonArray,
    transformJson
  };
