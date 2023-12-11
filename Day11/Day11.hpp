#ifndef DAY_11_HPP
#define DAY_11_HPP

#include "Solver.hpp"

namespace DAY11
{

class Day11 : public Solver
{
  public:
  Day11();
  ~Day11();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
};

} // namespace DAY11

#endif // DAY_11_HPP