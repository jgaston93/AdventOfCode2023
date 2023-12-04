#include <cstdio>
#include <cstring>

#include "Day04.hpp"

Day04::Day04() : m_card_count(0), m_cards(NULL) {}

Day04::~Day04()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day04::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day04::Configure(const ConfigurationResource configuration_resource,
                      RETURN_CODE_TYPE::Value& return_code)
{

  FILE* fp = fopen(configuration_resource.c_str(), "r");
  if (fp == NULL)
  {
    return_code = RETURN_CODE_TYPE::INVALID_PARAM;
  }

  if (return_code == RETURN_CODE_TYPE::NO_ERROR)
  {
    char line[256] = {0};
    char* line_ptr = &line[0];

    fgets(line, sizeof(line), fp);
    m_card_count++;

    //
    unsigned int winning_number_count = 0;
    unsigned int my_number_count      = 0;

    // Strip card info and get pointers to
    // winning numbers and my numbers
    line_ptr                 = strtok(line_ptr, ":");
    char* winning_number_ptr = strtok(NULL, "|");
    char* my_number_ptr      = strtok(NULL, "\n");

    // Count number of winning numbers
    winning_number_ptr = strtok(winning_number_ptr, " ");
    while (winning_number_ptr != NULL)
    {
      winning_number_count++;
      winning_number_ptr = strtok(NULL, " ");
    }

    // Count number of my numbers
    my_number_ptr = strtok(my_number_ptr, " ");
    while (my_number_ptr != NULL)
    {
      my_number_count++;
      my_number_ptr = strtok(NULL, " ");
    }

    // Get total number of cards
    while (fgets(line, sizeof(line), fp) != NULL)
      m_card_count++;

    // Reset back to start of file
    fseek(fp, 0, SEEK_SET);

    m_cards              = new Card[m_card_count];
    unsigned int card_id = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
      m_cards[card_id].card_number          = card_id + 1;
      m_cards[card_id].winning_number_count = winning_number_count;
      m_cards[card_id].my_number_count      = my_number_count;
      m_cards[card_id].winning_numbers = new unsigned int[winning_number_count];
      m_cards[card_id].my_numbers      = new unsigned int[my_number_count];

      // Strip card info and get pointers to
      // winning numbers and my numbers
      line_ptr           = strtok(line_ptr, ":");
      winning_number_ptr = strtok(NULL, "|");
      my_number_ptr      = strtok(NULL, "\n");

      // Get winning numbers
      unsigned int number_counter = 0;
      winning_number_ptr          = strtok(winning_number_ptr, " ");
      while (winning_number_ptr != NULL)
      {
        unsigned int number = 0;
        sscanf(winning_number_ptr, "%lu", &number);
        m_cards[card_id].winning_numbers[number_counter++] = number;
        winning_number_ptr                                 = strtok(NULL, " ");
      }

      // Get my numbers
      number_counter = 0;
      my_number_ptr  = strtok(my_number_ptr, " ");
      while (my_number_ptr != NULL)
      {
        unsigned int number = 0;
        sscanf(my_number_ptr, "%lu", &number);
        m_cards[card_id].my_numbers[number_counter++] = number;
        my_number_ptr                                 = strtok(NULL, " ");
      }

      card_id++;
    }

    fclose(fp);

    for (unsigned int i = 0; i < m_card_count; i++)
    {
      for (unsigned int j = 0; j < m_cards[i].winning_number_count; j++)
      {
        printf("%lu ", m_cards[i].winning_numbers[j]);
      }
      printf("\n");
      for (unsigned int j = 0; j < m_cards[i].my_number_count; j++)
      {
        printf("%lu ", m_cards[i].my_numbers[j]);
      }
      printf("\n\n");
    }
  }

  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day04::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day04::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}