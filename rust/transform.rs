use chrono::{DateTime, NaiveDateTime, Utc};
use serde::{Deserialize, Serialize};
use serde_json::Value;

#[derive(Deserialize)]
struct InputData {
    id: String,
    string: String,
    number: i32,
    null: Option<Value>,
    array: Vec<i32>,
    object: Value,
    timestamp: i64,
}

#[derive(Serialize)]
struct OutputData {
    id: String,
    string: String,
    number: i32,
    val: i32,
    sum: i32,
    obj: Value,
    timestamp: String,
}

pub fn transform_json(json_str: &str) -> String {
    let data: InputData = serde_json::from_str(json_str).unwrap();
    let naive_datetime = NaiveDateTime::from_timestamp_opt(data.timestamp, 0);
    let iso_timestamp: DateTime<Utc> = DateTime::from_utc(naive_datetime.unwrap(), Utc);

    let new_data = OutputData {
        id: data.id.chars().rev().take(8).collect::<String>().chars().rev().collect(),
        string: data.string.split_whitespace().next().unwrap().to_string(),
        number: data.number + 1,
        val: if data.null.is_some() { 1 } else { 0 },
        sum: data.array.iter().sum::<i32>(),
        obj: data.object,
        timestamp: iso_timestamp.to_string(),
    };

    serde_json::to_string(&new_data).unwrap()
}


#[test]
fn test_transform_json() {
    let json_str = r#"{
        "id": "8006e2f7-cba5-4385-b16b-389e04339f4b",
        "string": "The quick brown fox jumps over the lazy dog",
        "number": 42,
        "null": null,
        "array": [1, 2, 3, 4, 5],
        "object": {
            "a": "apple",
            "b": "banana",
            "c": "carrot"
        },
        "timestamp": 1646457600
    }"#;

    let expected_output = r#"{
        "id": "04339f4b",
        "string":"The",
        "number":43,
        "val":0,
        "sum":15,
        "obj": {
            "a":"apple",
            "b":"banana",
            "c":"carrot"
        },
        "timestamp":"2022-03-05 05:20:00 UTC"
    }"#.to_string().replace(" ", "").replace("\n", "");

    let output = transform_json(json_str).replace(" ", "").replace("\n", "");
    
    assert_eq!(output, expected_output);
}
