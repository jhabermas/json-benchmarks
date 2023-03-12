use std::env;
use std::fs::File;
use std::io::Write;
use std::time::Instant;

mod generate;
mod transform;

fn main() {
    let mut num_objects = 10000;
    let mut num_iterations = 3;
    let mut output_file = "rust_results.csv";
    
    let args: Vec<String> = env::args().collect();
    if args.len() == 4
    {
        num_objects = args[1].parse().unwrap();
        num_iterations = args[2].parse().unwrap();
        output_file = &args[3];
    }

    let mut results = Vec::new();

    for i in 0..num_iterations {
        let json_objs = generate::generate_json_objects(num_objects);
        let start = Instant::now();
        for json_str in &json_objs {
            transform::transform_json(json_str);
        }
        let elapsed = start.elapsed().as_micros();
        results.push(elapsed);
        println!("Iteration {}: {} microseconds", i + 1, elapsed);
    }

    let avg_time = results.iter().sum::<u128>() as f64 / num_iterations as f64 / 1000 as f64;
    println!("Average time per iteration: {} seconds", avg_time);

    let mut file = File::create(output_file).unwrap();
    writeln!(file, "{}", "rust").unwrap();
    writeln!(file, "{}", avg_time).unwrap();
}
