#ifndef DAY_06_HPP
#define DAY_06_HPP

#include "Solver.hpp"

struct Race
{
  unsigned long long int time;
  unsigned long long int distance;
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
  unsigned int m_num_race;
  struct Race m_races[256];
};

#endif // DAY_06_HPP