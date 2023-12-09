#ifndef DAY_07_HPP
#define DAY_07_HPP

#include "Solver.hpp"

namespace DAY07
{

const uint32_t num_cards_per_hand = 5;

enum HandType
{
  FIVE_OF_A_KIND,
  FOUR_OF_A_KIND,
  FULL_HOUSE,
  THREE_OF_A_KIND,
  TWO_PAIR,
  ONE_PAIR,
  HIGH_CARD,
  NUM_HAND_TYPE,
};

struct Hand
{
  HandType hand_type = NUM_HAND_TYPE;
  char cards[num_cards_per_hand];
  uint32_t bid = 0;
};

class Day07 : public Solver
{
  public:
  Day07();
  ~Day07();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  uint32_t m_num_hands = 0;
  struct Hand m_hands[2048];
  uint32_t m_ranks[2048];
};

} // namespace DAY07

#endif // DAY_07_HPP