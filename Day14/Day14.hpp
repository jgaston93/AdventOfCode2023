#ifndef DAY_14_HPP
#define DAY_14_HPP

#include "Solver.hpp"

namespace DAY14
{

const uint32_t MAX_DISH_SIZE = 100;
const uint32_t MAX_NUM_DISH  = 2;

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
  uint32_t m_current_dish;
  uint32_t m_dish_size;
  char m_dish[MAX_NUM_DISH][MAX_DISH_SIZE][MAX_DISH_SIZE];
};

} // namespace DAY14

#endif // DAY_14_HPP