#ifndef DAY_01_HPP
#define DAY_01_HPP

#include <cstdio>

#include "Solver.hpp"

class Day01 : public Solver
{
  public:
  Day01();
  ~Day01();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  const unsigned int m_num_strings;
  const unsigned int m_max_string_length;
  char** m_digit_strings;
  FILE* m_fp;
};

#endif // DAY_01_HPP