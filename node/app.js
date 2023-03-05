const { v4: uuidv4 } = require('uuid');

function generate_json_array(n) {
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

const json_array = generate_json_array(3);
json_array.forEach(json_str => console.log(json_str));
