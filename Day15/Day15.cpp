#include <cstdio>
#include <cstring>

#include "Day15.hpp"

using namespace DAY15;

Day15::Day15() : m_num_strings(0) {}

Day15::~Day15()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day15::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
  memset(m_strings, 0, sizeof(m_strings));
}

void Day15::Configure(const ConfigurationResource configuration_resource,
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
    char line[MAX_LINE_SIZE + 1] = {0};

    fgets(line, sizeof(line), fp);

    char* line_ptr = &(line[0]);
    line_ptr       = strtok(line_ptr, ",");
    while (line_ptr != NULL)
    {
      strcpy(m_strings[m_num_strings++], line_ptr);
      line_ptr = strtok(NULL, ",");
    }

    fclose(fp);
  }
}

void Day15::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  for (uint32_t i = 0; i < m_num_strings; i++)
  {
    bool add_lens         = true;
    char* operator_string = strchr(m_strings[i], '=');
    if (operator_string == NULL)
    {
      operator_string = strchr(m_strings[i], '-');
      add_lens        = false;
    }

    *operator_string       = '\0';
    uint32_t string_length = strlen(m_strings[i]);
    uint32_t current_value = 0;
    for (uint32_t j = 0; j < string_length; j++)
    {
      current_value += m_strings[i][j];
      current_value *= 17;
      current_value %= 256;
    }
    if (add_lens)
      m_boxes[current_value].AddLens(m_strings[i],
                                     *(operator_string + 1) - '0');
    else
      m_boxes[current_value].RemoveLens(m_strings[i]);
  }

  uint32_t sum = 0;
  for (uint32_t i = 0; i < MAX_NUM_BOXES; i++)
  {
    for (uint32_t j = 0; j < m_boxes[i].num_lenses; j++)
    {
      sum += (i + 1) * (j + 1) * m_boxes[i].lenses[j].focal_length;
    }
  }
  printf("Part 2 solution: %lu\n", sum);
}

void Day15::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}
