#ifndef DAY_13_HPP
#define DAY_13_HPP

#include "Solver.hpp"

namespace DAY13
{

struct Map
{
  uint32_t num_rows = 0;
  uint32_t num_cols = 0;
  char grid[64][64];
};

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
  uint32_t m_num_maps;
  Map m_maps[1024];
};

} // namespace DAY13

#endif // DAY_13_HPP