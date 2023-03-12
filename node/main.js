const { runBenchmark } = require('./benchmark');

function main() {
    const args = process.argv.slice(2);
    const numObjects = parseInt(args[0]) || 100000;
    const numRuns = parseInt(args[1]) || 3;
    const csvFilename = args[2] || 'benchmark_results.csv';
    
    console.log(`Running benchmark with ${numObjects} objects over ${numRuns} runs...`);
    console.log(`Saving results to ${csvFilename}`);
    
    const results = runBenchmark(numObjects, numRuns, csvFilename);
    console.log(results);
}

main();
