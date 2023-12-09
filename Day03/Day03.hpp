#ifndef DAY_03_HPP
#define DAY_03_HPP

#include "Solver.hpp"

namespace DAY03
{
enum Type
{
  NUMBER,
  SYMBOL,
  EMPTY
};

struct Node
{
  uint32_t id;
  Type type;

  Node(uint32_t id, Type type) : id(id), type(type){};
};

struct NumberNode : public Node
{
  uint32_t part_number = 0;

  NumberNode(uint32_t id, uint32_t number)
    : Node(id, NUMBER), part_number(number){};
};

struct SymbolNode : public Node
{
  char symbol = 0;

  SymbolNode(uint32_t id, char symbol) : Node(id, SYMBOL), symbol(symbol){};
};

struct EmptyNode : public Node
{
  EmptyNode(uint32_t id) : Node(id, EMPTY){};
};

class Day03 : public Solver
{
  public:
  Day03();
  ~Day03();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  Node*** m_nodes;
  uint32_t m_num_rows;
  uint32_t m_num_columns;
};

} // namespace DAY03

#endif // DAY_03_HPP