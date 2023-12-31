#ifndef DAY_06_HPP
#define DAY_06_HPP

#include "Solver.hpp"

namespace DAY06
{

struct Race
{
  uint64_t time;
  uint64_t distance;
};

class Day06 : public Solver
{
  public:
  Day06();
  ~Day06();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  uint32_t m_num_race;
  struct Race m_races[256];
};

} // namespace DAY06

#endif // DAY_06_HPP