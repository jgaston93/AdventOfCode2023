#ifndef DAY_14_HPP
#define DAY_14_HPP

#include "Solver.hpp"

namespace DAY14
{

class Day14 : public Solver
{
  public:
  Day14();
  ~Day14();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
};

} // namespace DAY14

#endif // DAY_14_HPP