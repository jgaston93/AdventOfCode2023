#include <cstring>

#include "Day01.hpp"

using namespace DAY01;

Day01::Day01()
  : m_num_strings(9), m_max_string_length(8), m_digit_strings(0), m_fp(NULL)
{
}

Day01::~Day01()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;

  Finalize(return_code);
}

void Day01::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  m_digit_strings = new char*[m_num_strings];
  for (unsigned int i = 0; i < m_num_strings; i++)
  {
    m_digit_strings[i] = new char[m_max_string_length];
  }

  strcpy(m_digit_strings[0], "one");
  strcpy(m_digit_strings[1], "two");
  strcpy(m_digit_strings[2], "three");
  strcpy(m_digit_strings[3], "four");
  strcpy(m_digit_strings[4], "five");
  strcpy(m_digit_strings[5], "six");
  strcpy(m_digit_strings[6], "seven");
  strcpy(m_digit_strings[7], "eight");
  strcpy(m_digit_strings[8], "nine");
}

void Day01::Configure(const ConfigurationResource configuration_resource,
                      RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  m_fp = fopen(configuration_resource.c_str(), "r");
  if (m_fp == NULL)
  {
    return_code = RETURN_CODE_TYPE::INVALID_PARAM;
  }
}

void Day01::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  char line[256];

  unsigned int part_1_solution = 0;
  unsigned int part_2_solution = 0;

  // iterate over each line in the file
  while (fgets(line, sizeof(line), m_fp) != NULL)
  {
    char current_char       = line[0];
    unsigned int line_index = 1;

    // used to track only numeric digits
    unsigned int digit_list_length = 0;
    unsigned int digit_list[32]    = {0};
    // used to track numeric and alphanumeric digits
    unsigned int full_digit_list_length = 0;
    unsigned int full_digit_list[32]    = {0};

    // iterate over each character in line until
    // newline or null terminator found
    while (current_char != '\n' && current_char != '\0')
    {
      unsigned int digit = 0;
      // check if character is a number
      if ('0' <= current_char && current_char <= '9')
      {
        // Add digit to list if size is not exceeded
        if (digit_list_length < (sizeof(digit_list) / sizeof(unsigned int)))
        {
          digit_list[digit_list_length++] = current_char - '0';
        }
        else
        {
          printf("Warning exceeded digit_list length\n");
        }

        // Add digit to full list if size is not exceeded
        if (full_digit_list_length <
            (sizeof(full_digit_list) / sizeof(unsigned int)))
        {
          full_digit_list[full_digit_list_length++] = current_char - '0';
        }
        else
        {
          printf("Warning exceeded full_digit_list length\n");
        }
      }
      // check if number is spelled out
      else
      {
        // get length of remaining line
        unsigned int line_length = strlen(&(line[line_index - 1]));

        // iterate over digit strings
        bool digit_found = false;
        for (unsigned int i = 0; i < 9 && !digit_found; i++)
        {
          // get length of digit string
          unsigned int digit_string_length = strlen(m_digit_strings[i]);

          // ensure that remaining line length is
          // at least as long as digit string length
          if (line_length >= digit_string_length)
          {
            // check if strings are equal
            if (strncmp(m_digit_strings[i], &(line[line_index - 1]),
                        digit_string_length) == 0)
            {
              if (full_digit_list_length <
                  (sizeof(full_digit_list) / sizeof(unsigned int)))
              {
                full_digit_list[full_digit_list_length++] = i + 1;
              }
              else
              {
                printf("Warning exceeded full_digit_list length\n");
              }
            }
          }
        }
      }
      current_char = line[line_index++];
    }
    if (digit_list_length > 0)
      part_1_solution +=
        (digit_list[0] * 10) + digit_list[digit_list_length - 1];

    if (full_digit_list_length > 0)
      part_2_solution +=
        (full_digit_list[0] * 10) + full_digit_list[full_digit_list_length - 1];
  }

  printf("Part 1 solution: %lu\n", part_1_solution);
  printf("Part 2 solution: %lu\n", part_2_solution);
}

void Day01::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  fclose(m_fp);
  for (unsigned int i = 0; i < m_num_strings; i++)
  {
    delete[] m_digit_strings[i];
  }
  delete[] m_digit_strings;
}