#ifndef DAY_12_HPP
#define DAY_12_HPP

#include "Solver.hpp"

namespace DAY12
{

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
};

} // namespace DAY12

#endif // DAY_12_HPP