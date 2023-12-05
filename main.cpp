#include <fstream>
#include <iostream>
#include <string>

#include "cxxopts.hpp"
#include "nlohmann/json.hpp"

#include "Day01/Day01.hpp"
#include "Day02/Day02.hpp"
#include "Day03/Day03.hpp"
#include "Day04/Day04.hpp"
#include "Day05/Day05.hpp"

using json = nlohmann::json;

int main(int argc, char** argv)
{
  // Configure cxxopts
  cxxopts::Options options("AOC Driver",
                           "Driver program for Advent of Code puzzles");

  options.add_options()("c,config", "Configuration File",
                        cxxopts::value<std::string>());

  // Parse command line arguments
  auto result = options.parse(argc, argv);

  // Check if configuration file is provided
  if (result.count("config") == 0)
  {
    std::cout << "Missing configuration file." << std::endl << std::endl;
    std::cout << options.help() << std::endl;
    return 1;
  }

  // Attempt to open configuration file
  std::ifstream f(result["config"].as<std::string>());
  if (!f)
  {
    std::cout << "Invalid configuration file: "
              << result["config"].as<std::string>() << std::endl;
    return 1;
  }

  // Parse configuration file
  json configuration_file;
  try
  {
    configuration_file = json::parse(f);
  } catch (...)
  {
    std::cout << "Failed to parse configuration file: "
              << result["config"].as<std::string>() << std::endl;
    return 1;
  }

  // Get solver from configuration file
  std::string solver_name;
  try
  {
    solver_name = configuration_file["solver"];
  } catch (...)
  {
    std::cout << "Error retrieving solver name from configuration file"
              << std::endl;
    return 1;
  }

  // Instantiate solver based on value from configuration file
  Solver* solver = NULL;
  if (solver_name.compare("Day01") == 0)
  {
    solver = new Day01();
  }
  else if (solver_name.compare("Day02") == 0)
  {
    solver = new Day02();
  }
  else if (solver_name.compare("Day03") == 0)
  {
    solver = new Day03();
  }
  else if (solver_name.compare("Day04") == 0)
  {
    solver = new Day04();
  }
  else if (solver_name.compare("Day05") == 0)
  {
    solver = new Day05();
  }
  else
  {
    std::cout << "Unsupported solver specified in configuration files: "
              << solver_name << std::endl;
    return 1;
  }

  // Get inpput file from configuration file
  ConfigurationResource configuration_resource;
  try
  {
    configuration_resource = configuration_file["input_file"];
  } catch (...)
  {
    std::cout << "Error retrieving input file name from configuration file"
              << std::endl;
    return 1;
  }

  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;

  solver->Initialize(return_code);

  if (return_code == RETURN_CODE_TYPE::NO_ERROR)
  {
    solver->Configure(configuration_resource, return_code);
  }
  else
  {
    std::cout << "Encountered error during solver initialization" << std::endl;
    return 1;
  }

  if (return_code == RETURN_CODE_TYPE::NO_ERROR)
  {
    solver->Solve(return_code);
  }
  else
  {
    std::cout << "Encountered error during solver configuration" << std::endl;
    return 1;
  }

  if (return_code == RETURN_CODE_TYPE::NO_ERROR)
  {
    solver->Finalize(return_code);
  }
  else
  {
    std::cout << "Encountered error while solving" << std::endl;
    return 1;
  }

  if (return_code != RETURN_CODE_TYPE::NO_ERROR)
  {
    std::cout << "Encountered error during solver finalization" << std::endl;
    return 1;
  }

  delete solver;

  return 0;
};