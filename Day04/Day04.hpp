#ifndef DAY_04_HPP
#define DAY_04_HPP

#include "Solver.hpp"

class Day04 : public Solver
{
  public:
  Day04();
  ~Day04();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
};

#endif // DAY_04_HPP