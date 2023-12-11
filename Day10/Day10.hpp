#ifndef DAY_10_HPP
#define DAY_10_HPP

#include <map>

#include "Solver.hpp"

namespace DAY10
{

const uint32_t MAX_NUM_ROWS            = 142;
const uint32_t MAX_NUM_COLS            = 142;
const uint32_t MAX_NUM_CONNECTED_TILES = 2;

enum TileType
{
  Vertical,
  Horizontal,
  NorthAndEast,
  NorthAndWest,
  SouthAndWest,
  SouthAndEast,
  Ground,
  Start
};

struct Tile
{
  TileType type     = Ground;
  Tile* north_tile  = NULL;
  Tile* south_tile  = NULL;
  Tile* east_tile   = NULL;
  Tile* west_tile   = NULL;
  uint32_t distance = 0xFFFFFFFF;
  bool visited      = false;
  bool main_loop    = false;
  int32_t loc_x     = 0;
  int32_t loc_y     = 0;
};

class Day10 : public Solver
{
  public:
  Day10();
  ~Day10();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  void MakeNorthConnection(int32_t row_index, int32_t col_index,
                           RETURN_CODE_TYPE::Value& return_code);
  void MakeSouthConnection(int32_t row_index, int32_t col_index,
                           RETURN_CODE_TYPE::Value& return_code);
  void MakeEastConnection(int32_t row_index, int32_t col_index,
                          RETURN_CODE_TYPE::Value& return_code);
  void MakeWestConnection(int32_t row_index, int32_t col_index,
                          RETURN_CODE_TYPE::Value& return_code);

  uint32_t m_num_rows;
  uint32_t m_num_cols;
  Tile m_tiles[MAX_NUM_ROWS][MAX_NUM_COLS];
  Tile* m_start_tile;
};

} // namespace DAY10

#endif // DAY_10_HPP