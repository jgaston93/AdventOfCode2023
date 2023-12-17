#ifndef DAY_16_HPP
#define DAY_16_HPP

#include "Solver.hpp"

namespace DAY16
{

const uint32_t MAX_GRID_SIZE = 110;
const uint32_t MAX_NUM_BEAMS = 8192;

enum TileType
{
  Empty,
  LeftMirror,
  RightMirror,
  VerticalSplitter,
  HorizontalSplitter,
};

struct Tile
{
  TileType type              = Empty;
  uint32_t energy_level      = 0;
  uint64_t num_visited_beams = 0;
  uint64_t visited_beams[MAX_NUM_BEAMS];
};

struct Beam
{
  uint64_t beam_id = 0;
  int32_t x        = 0;
  int32_t y        = 0;
  int32_t vel_x    = 0;
  int32_t vel_y    = 0;
};

class Day16 : public Solver
{
  public:
  Day16();
  ~Day16();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  uint32_t m_grid_size;
  Tile m_tiles[MAX_GRID_SIZE][MAX_GRID_SIZE];
  uint32_t m_num_beams;
  Beam m_beams[MAX_NUM_BEAMS];
  uint64_t m_beam_id;

  void Interact(Beam& beam, Tile& tile);
};

} // namespace DAY16

#endif // DAY_16_HPP