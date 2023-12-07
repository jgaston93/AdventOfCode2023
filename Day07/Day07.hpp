#ifndef DAY_07_HPP
#define DAY_07_HPP

#include "Solver.hpp"

class Day07 : public Solver
{
  public:
  Day07();
  ~Day07();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
};

#endif // DAY_07_HPP