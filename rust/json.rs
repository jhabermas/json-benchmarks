extern crate serde_json;
extern crate uuid;

use serde_json::{Result, Value};
use uuid::Uuid;

use std::time::{SystemTime, UNIX_EPOCH};

fn generate_json_objects(n: i32) -> Vec<String> {
    let mut json_array: Vec<String> = Vec::new();
    for i in 0..n {
        let obj: Value = json!({
            "id": Uuid::new_v4().to_string(),
            "string": "hello world",
            "number": rand::random::<i32>() % 201 - 100,
            "boolean": rand::random::<bool>(),
            "null": serde_json::Value::Null,
            "array": vec![1, 2, 3, 4, 5, 6, 7, i],
            "object": { "key": i },
            "timestamp": SystemTime::now().duration_since(UNIX_EPOCH).unwrap().as_secs()
        });
        let json_str = serde_json::to_string(&obj).unwrap();
        json_array.push(json_str);
    }
    return json_array;
}


#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        let result = 2 + 2;
        assert_eq!(result, 4);
    }
}