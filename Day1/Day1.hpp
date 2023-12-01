#ifndef DAY_1_HPP
#define DAY_1_HPP

#include <cstdio>

#include "Solver.hpp"

class Day1 : public Solver
{
  public:
  Day1();
  ~Day1();
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

#endif // DAY_1_HPP