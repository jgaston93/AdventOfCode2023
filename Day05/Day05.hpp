#ifndef DAY_05_HPP
#define DAY_05_HPP

#include "Solver.hpp"

namespace DAY05
{

struct SeedRange
{
  unsigned int start  = 0;
  unsigned int length = 0;
};

struct MappingRange
{
  unsigned int destination_start = 0;
  unsigned int source_start      = 0;
  unsigned int length            = 0;
};

struct Mapping
{
  unsigned int num_ranges = 0;
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
  unsigned int m_num_seeds;
  unsigned int m_seeds[256];
  unsigned int m_num_mappings;
  struct Mapping m_mappings[256];
};

} // namespace DAY05

#endif // DAY_05_HPP