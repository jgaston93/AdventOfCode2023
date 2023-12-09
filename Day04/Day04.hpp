#ifndef DAY_04_HPP
#define DAY_04_HPP

#include "Solver.hpp"

namespace DAY04
{

struct Card
{
  uint32_t card_number;
  uint32_t card_count;
  uint32_t winning_number_count;
  uint32_t my_number_count;
  uint32_t* winning_numbers;
  uint32_t* my_numbers;
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
  uint32_t m_card_count;
  struct Card* m_cards;
};

} // namespace DAY04

#endif // DAY_04_HPP