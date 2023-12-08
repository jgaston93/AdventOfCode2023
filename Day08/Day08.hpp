#ifndef DAY_08_HPP
#define DAY_08_HPP

#include "Solver.hpp"

namespace DAY08
{

struct Node
{
  char name[4];
  char left_name[4];
  char right_name[4];
  Node* left;
  Node* right;
};

class Day08 : public Solver
{
  public:
  Day08();
  ~Day08();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  unsigned int m_num_nodes;
  Node m_nodes[1024];
  unsigned int m_num_start_nodes;
  Node* m_start_nodes[6];
  unsigned int m_num_directions;
  char m_directions[512];
};

} // namespace DAY08

#endif // DAY_08_HPP