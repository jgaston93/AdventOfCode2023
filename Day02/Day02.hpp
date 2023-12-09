#ifndef DAY_02_HPP
#define DAY_02_HPP

#include "Solver.hpp"

namespace DAY02
{
struct Game
{
  uint32_t id       = 0;
  uint32_t num_sets = 0;
  struct Set* sets      = NULL;
};

struct Set
{
  uint32_t num_red   = 0;
  uint32_t num_green = 0;
  uint32_t num_blue  = 0;
};

class Day02 : public Solver
{
  public:
  Day02();
  ~Day02();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  uint32_t m_num_games;
  struct Game* m_games;
};

} // namespace DAY02

#endif // DAY_02_HPP