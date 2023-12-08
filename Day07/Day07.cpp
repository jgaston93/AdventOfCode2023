#include <algorithm>
#include <cstdio>
#include <cstring>

#include "Day07.hpp"

using namespace DAY07;

bool hand_comparator(Hand a, Hand b)
{
  if (a.hand_type > b.hand_type)
    return true;
  else if (a.hand_type < b.hand_type)
    return false;
  else
  {
    for (unsigned int i = 0; i < num_cards_per_hand; i++)
    {
      if (a.cards[i] < b.cards[i])
        return true;
      else if (a.cards[i] > b.cards[i])
        return false;
    }
  }
  return true;
}

void card2number(char& card)
{
  if (card == '2')
    card = 1;
  else if (card == '3')
    card = 2;
  else if (card == '4')
    card = 3;
  else if (card == '5')
    card = 4;
  else if (card == '6')
    card = 5;
  else if (card == '7')
    card = 6;
  else if (card == '8')
    card = 7;
  else if (card == '9')
    card = 8;
  else if (card == 'T')
    card = 9;
  else if (card == 'J')
    card = 0;
  else if (card == 'Q')
    card = 10;
  else if (card == 'K')
    card = 11;
  else if (card == 'A')
    card = 12;
}

Day07::Day07() : m_num_hands(0) {}

Day07::~Day07()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day07::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day07::Configure(const ConfigurationResource configuration_resource,
                      RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  FILE* fp = fopen(configuration_resource.c_str(), "r");
  if (fp == NULL)
  {
    return_code = RETURN_CODE_TYPE::INVALID_PARAM;
  }

  if (return_code == RETURN_CODE_TYPE::NO_ERROR)
  {
    char HandTypeString[][256]{
      "FIVE_OF_A_KIND", "FOUR_OF_A_KIND", "FULL_HOUSE", "THREE_OF_A_KIND",
      "TWO_PAIR",       "ONE_PAIR",       "HIGH_CARD",
    };

    char line[256] = {0};

    while (fgets(line, sizeof(line), fp) != NULL)
    {
      Hand& hand = m_hands[m_num_hands];
      sscanf(line, "%c%c%c%c%c %lu", &(hand.cards[0]), &(hand.cards[1]),
             &(hand.cards[2]), &(hand.cards[3]), &(hand.cards[4]), &(hand.bid));

      for (unsigned int i = 0; i < num_cards_per_hand; i++)
        card2number(hand.cards[i]);

      char card_count_list[13] = {0};

      for (unsigned int i = 0; i < num_cards_per_hand; i++)
        card_count_list[hand.cards[i]]++;

      unsigned int max_card_count       = 0;
      unsigned int max_card_count_index = 1;
      for (unsigned int i = 1; i < 13; i++)
      {
        if (card_count_list[i] > max_card_count)
        {
          max_card_count       = card_count_list[i];
          max_card_count_index = i;
        }
      }

      if (card_count_list[0] > 0)
      {
        card_count_list[max_card_count_index] += card_count_list[0];
        card_count_list[0] = 0;
      }

      std::sort(card_count_list, card_count_list + 13, std::greater<char>());

      // Five of a kind
      if (card_count_list[0] == num_cards_per_hand)
        hand.hand_type = FIVE_OF_A_KIND;
      // Four of a kind
      else if (card_count_list[0] == num_cards_per_hand - 1)
        hand.hand_type = FOUR_OF_A_KIND;
      // Full house
      else if (card_count_list[0] == num_cards_per_hand - 2 &&
               card_count_list[1] == 2)
        hand.hand_type = FULL_HOUSE;
      // Three of a kind
      else if (card_count_list[0] == num_cards_per_hand - 2 &&
               card_count_list[1] == 1)
        hand.hand_type = THREE_OF_A_KIND;
      // Two pair
      else if (card_count_list[0] == 2 && card_count_list[1] == 2)
        hand.hand_type = TWO_PAIR;
      // One pair
      else if (card_count_list[0] == 2)
        hand.hand_type = ONE_PAIR;
      // High card
      else
        hand.hand_type = HIGH_CARD;

      m_num_hands++;
    }

    fclose(fp);
  }
}

void Day07::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
  std::sort(m_hands, m_hands + m_num_hands, hand_comparator);

  unsigned int total_winnings = 0;
  for (unsigned int i = 0; i < m_num_hands; i++)
  {
    total_winnings += (i + 1) * m_hands[i].bid;
  }

  printf("Part 1 solution: %lu\n", total_winnings);
}

void Day07::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}