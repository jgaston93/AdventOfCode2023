#ifndef DAY_05_HPP
#define DAY_05_HPP

#include "Solver.hpp"

struct Range
{
  unsigned int destination_start = 0;
  unsigned int source_start      = 0;
  unsigned int range             = 0;
};

struct Mapping
{
  unsigned int num_ranges = 0;
  Range ranges[256];
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

#endif // DAY_05_HPP