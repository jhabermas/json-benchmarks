const fs = require('fs');
const { generateJsonArray, transformJson  } = require('./transform_json');

function transformAll(transformJsonFn, jsonArray) {
  const transformed = [];
  for (const jsonStr of jsonArray) {
    transformed.push(transformJsonFn(jsonStr));
  }
  if (transformed.length !== jsonArray.length) {
    throw new Error('Error transforming all JSON objects.');
  }
}

function benchmarkTransformJson(transformJsonFn, jsonArray, numRuns) {
  console.log(`Benchmarking using ${jsonArray.length} objects over ${numRuns} runs...`);
  const startTime = Date.now();
  for (let i = 0; i < numRuns; i++) {
    transformAll(transformJsonFn, jsonArray);
  }
  const endTime = Date.now();
  const totalTime = (endTime - startTime) / numRuns;
  console.log(`Average time: ${totalTime.toFixed(3)} seconds`);
  return totalTime;
}

function benchmarkAllTransformJson(jsonArray, numRuns) {
  const times = [];
  times.push(benchmarkTransformJson(transformJson, jsonArray, numRuns));
  return times;
}

function writeResultsToCsv(resultRows, filename) {
  const csvString = 'node.js\n' + resultRows.join('\n');
  fs.writeFileSync(filename, csvString);
}

function runBenchmark(numObjects, numRuns, filename) {
  const jsonArray = generateJsonArray(numObjects);
  const resultRows = benchmarkAllTransformJson(jsonArray, numRuns);
  writeResultsToCsv(resultRows, filename);
}

module.exports = {
  runBenchmark,
};
