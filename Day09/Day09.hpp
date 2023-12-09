#ifndef DAY_09_HPP
#define DAY_09_HPP

#include "Solver.hpp"

const uint32_t max_report_length  = 200;
const uint32_t max_history_length = 21;

namespace DAY09
{

class Day09 : public Solver
{
  public:
  Day09();
  ~Day09();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  uint32_t m_report_length;
  uint32_t m_history_length;
  int32_t m_report[max_report_length][max_history_length];
};

} // namespace DAY09

#endif // DAY_09_HPP