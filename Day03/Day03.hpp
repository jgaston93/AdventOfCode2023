#ifndef DAY_03_HPP
#define DAY_03_HPP

#include "Solver.hpp"

enum Type
{
  NUMBER,
  SYMBOL,
  EMPTY
};

struct Node
{
  unsigned int id;
  Type type;

  Node(unsigned int id, Type type) : id(id), type(type){};
};

struct NumberNode : public Node
{
  unsigned int part_number = 0;

  NumberNode(unsigned int id, unsigned int number)
    : Node(id, NUMBER), part_number(number){};
};

struct SymbolNode : public Node
{
  char symbol = 0;

  SymbolNode(unsigned int id, char symbol) : Node(id, SYMBOL), symbol(symbol){};
};

struct EmptyNode : public Node
{
  EmptyNode(unsigned int id) : Node(id, EMPTY){};
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
  unsigned int m_num_rows;
  unsigned int m_num_columns;
};

#endif // DAY_03_HPP