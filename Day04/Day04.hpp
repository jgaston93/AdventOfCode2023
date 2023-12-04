#ifndef DAY_04_HPP
#define DAY_04_HPP

#include "Solver.hpp"

struct Card
{
  unsigned int card_number;
  unsigned int winning_number_count;
  unsigned int my_number_count;
  unsigned int* winning_numbers;
  unsigned int* my_numbers;
};

class Day04 : public Solver
{
  public:
  Day04();
  ~Day04();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  unsigned int m_card_count;
  struct Card* m_cards;
};

#endif // DAY_04_HPP