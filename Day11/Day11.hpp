#ifndef DAY_11_HPP
#define DAY_11_HPP

#include "Solver.hpp"

namespace DAY11
{

const uint32_t MAX_NUM_ROWS = 140;
const uint32_t MAX_NUM_COLS = 140;

enum TileType
{
  Space,
  Galaxy,
};

struct Tile
{
  uint32_t id            = 0;
  TileType type          = Space;
  uint32_t distance      = 1;
  uint32_t real_distance = 1;
};

struct Position
{
  int32_t x = 0;
  int32_t y = 0;
};

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
  uint32_t m_num_rows;
  uint32_t m_num_cols;
  Tile m_space[MAX_NUM_ROWS][MAX_NUM_COLS];
  uint32_t m_num_galaxies;
  Position* m_galaxy_coordinate_list;
};

} // namespace DAY11

#endif // DAY_11_HPP