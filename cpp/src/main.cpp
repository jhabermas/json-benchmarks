#include "boost_json.h"
#include "glaze_json.h"
#include "nl_json.h"
#include "simd_json.h"

#include <boost/program_options.hpp>

#include <iostream>
#include <fstream>
#include <chrono>
#include <stdexcept>

namespace fs = std::filesystem;
namespace po = boost::program_options;
namespace chrono = std::chrono;
using boost_json::generate_json;

std::tuple<int, int, std::string> parse_commandline_args(int argc, char** argv)
{
    int num_items, num_iterations;
    std::string output_file;
    po::options_description desc("Options");
    desc.add_options()
        ("help", "produce help message")
        ("num-items,n", po::value<int>(&num_items)->default_value(100000), "number of items in JSON array")
        ("num-runs,r", po::value<int>(&num_iterations)->default_value(3), "number of iterations to run benchmark")
        ("output-file,o", po::value<std::string>(&output_file)->default_value("results.json"), "output file name");
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
    } catch (std::exception& e) {
        std::cerr << "Error parsing command line arguments: " << e.what() << std::endl;
        std::exit(1);
    }
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        std::exit(0);
    }
    po::notify(vm);

    return {num_items, num_iterations, output_file};
}

void save_results(const fs::path& path, const std::map<std::string, double>& results)
{
    size_t col = 0;
    std::string headers{};
    std::string values{};
    for (const auto& kv : results)
    {
        headers.append(kv.first);
        values.append(std::to_string(kv.second));
        if (++col < results.size())
        {
            headers.append(",");
            values.append(",");
        }
    }

    std::cout << headers << "\n" << values << std::endl;
    std::ofstream out(path);
    out << headers << "\n" << values;
}

int main(int argc, char** argv) {
    auto [num_items, num_runs, output_file] = parse_commandline_args(argc, argv);
    auto run_benchmark = [runs = num_runs](auto&& func, const auto& data)
    {
        double total_time = 0;
        for (int i = 0; i < runs; i++) {
            auto start_time = chrono::high_resolution_clock::now();
            for (const auto& json_str : data)
            {
                func(json_str);
            }
            auto end_time = chrono::high_resolution_clock::now();
            total_time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }
        return total_time / runs / 1000.0;
    };

    std::cout << "Generating data" << std::endl;
    const auto& json_data = generate_json(num_items);
    std::cout << "Running boost" << std::endl;
    auto boost_json_time = run_benchmark(boost_json::transform_json, json_data);
    std::cout << "Running Glaze" << std::endl;
    auto glaze_json_time = run_benchmark(glaze_json::transform_json, json_data);
    std::cout << "Running nl" << std::endl;
    auto nl_json_time = run_benchmark(nlohmann_json::transform_json, json_data);
    std::cout << "Running simd" << std::endl;
    auto simd_json_time = run_benchmark(simd_json::transform_json, json_data);
    std::cout << "Done" << std::endl;
    save_results(
        output_file, {
            {"boost_json", boost_json_time},
            {"glaze", glaze_json_time},
            {"nlohmann_json", nl_json_time},
            {"simdjson", simd_json_time}
        }
    );

    return 0;
}