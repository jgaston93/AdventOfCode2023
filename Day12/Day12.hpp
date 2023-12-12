#ifndef DAY_12_HPP
#define DAY_12_HPP

#include "Solver.hpp"

namespace DAY12
{

const uint32_t MAX_NUM_RECORDS = 1000;

struct Record
{
  char spring_conditions[32];
  uint32_t num_sets = 0;
  uint32_t sets[16];
};

class Day12 : public Solver
{
  public:
  Day12();
  ~Day12();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  uint32_t m_num_records;
  Record m_records[MAX_NUM_RECORDS];
};

} // namespace DAY12

#endif // DAY_12_HPP