#include <iostream>
#include <string>

#include "cxxopts.hpp"

#include "Day1/Day1.hpp"

int main(int argc, char** argv)
{
  cxxopts::Options options("AOC Driver",
                           "Driver program for Advent of Code puzzles");

  options.add_options()("c,config", "Configuration File");

  auto result = options.parse(argc, argv);

  if (result.count("config") == 0)
  {
    std::cout << "Missing configuration file." << std::endl << std::endl;
    std::cout << options.help() << std::endl;
    return 1;
  }

  Solver* solver = new Day1();

  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;

  solver->Initialize(return_code);

  if (return_code == RETURN_CODE_TYPE::NO_ERROR)
  {
    ConfigurationResource configuration_resource = "input.txt";
    solver->Configure(configuration_resource, return_code);
  }

  if (return_code == RETURN_CODE_TYPE::NO_ERROR)
  {
    solver->Solve(return_code);
  }

  if (return_code == RETURN_CODE_TYPE::NO_ERROR)
  {
    solver->Finalize(return_code);
  }

  return 0;
};