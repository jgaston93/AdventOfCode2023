#ifndef DAY_05_HPP
#define DAY_05_HPP

#include "Solver.hpp"

namespace DAY05
{

struct SeedRange
{
  uint32_t start  = 0;
  uint32_t length = 0;
};

struct MappingRange
{
  uint32_t destination_start = 0;
  uint32_t source_start      = 0;
  uint32_t length            = 0;
};

struct Mapping
{
  uint32_t num_ranges = 0;
  MappingRange ranges[256];
};

class Day05 : public Solver
{
  public:
  Day05();
  ~Day05();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  uint32_t m_num_seeds;
  uint32_t m_seeds[256];
  uint32_t m_num_mappings;
  struct Mapping m_mappings[256];
};

} // namespace DAY05

#endif // DAY_05_HPP