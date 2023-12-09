#ifndef DAY_01_HPP
#define DAY_01_HPP

#include <cstdio>

#include "Solver.hpp"

namespace DAY01
{

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
  const uint32_t m_num_strings;
  const uint32_t m_max_string_length;
  char** m_digit_strings;
  FILE* m_fp;
};

} // namespace DAY01

#endif // DAY_01_HPP