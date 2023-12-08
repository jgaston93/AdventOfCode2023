#ifndef DAY_08_HPP
#define DAY_08_HPP

#include "Solver.hpp"

class Day08 : public Solver
{
  public:
  Day08();
  ~Day08();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
};

#endif // DAY_08_HPP