#include <cstring>

#include "Day01.hpp"

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

  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day01::Configure(const ConfigurationResource configuration_resource,
                      RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  m_fp = fopen(static_cast<const char*>(configuration_resource), "r");
  if (m_fp == NULL)
  {
    return_code = RETURN_CODE_TYPE::INVALID_PARAM;
  }
}

void Day01::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  char line[256];

  unsigned int calibration_values_sum = 0;

  // iterate over each line in the file
  while (fgets(line, sizeof(line), m_fp) != NULL)
  {
    unsigned int first = 0, last = 0;
    char current_char       = line[0];
    unsigned int line_index = 1;
    bool first_digit_found  = false;

    // iterate over each character in line until
    // newline or null terminator found
    while (current_char != '\n' && current_char != '\0')
    {
      unsigned int digit = 0;
      bool digit_found   = false;
      // check if character is a number
      if ('0' <= current_char && current_char <= '9')
      {
        digit       = current_char - '0';
        digit_found = true;
      }
      // check if number is spelled out
      else
      {
        // get length of remaining line
        unsigned int line_length = strlen(&(line[line_index - 1]));

        // iterate over digit strings
        for (unsigned int i = 0; i < 9 && !digit_found; i++)
        {
          // get length of digit string
          unsigned int digit_string_length = strlen(m_digit_strings[i]);
          // strlen(static_cast<const char*>(&(m_digit_strings[i])));

          // ensure that remaining line length is
          // at least as long as digit string length
          if (line_length >= digit_string_length)
          {
            // check if strings are equal
            if (strncmp(m_digit_strings[i], &(line[line_index - 1]),
                        digit_string_length) == 0)
            {
              digit       = i + 1;
              digit_found = true;
            }
          }
        }
      }

      if (digit_found)
      {
        // Set last to current found digit
        last = digit;
        // If first digit is found set the first character
        if (!first_digit_found)
        {
          first             = digit;
          first_digit_found = true;
        }
      }

      current_char = line[line_index++];
    }
    calibration_values_sum += (first * 10) + last;
  }

  printf("Sum of all calibration values is %lu\n", calibration_values_sum);
}

void Day01::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  fclose(m_fp);
  for (unsigned int i = 0; i < m_num_strings; i++)
  {
    delete[] m_digit_strings[i];
  }
  delete[] m_digit_strings;
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}