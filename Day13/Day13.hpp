#ifndef DAY_13_HPP
#define DAY_13_HPP

#include "Solver.hpp"

namespace DAY13
{

class Day13 : public Solver
{
  public:
  Day13();
  ~Day13();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
};

} // namespace DAY13

#endif // DAY_13_HPP