#include <cstdio>
#include <cstring>
#include <math.h>

#include "Day12.hpp"

using namespace DAY12;

Day12::Day12() : m_num_records(0) {}

Day12::~Day12()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day12::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
  memset(m_records, 0, sizeof(m_records));
}

void Day12::Configure(const ConfigurationResource configuration_resource,
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
    char line[512] = {0};

    while (fgets(line, sizeof(line), fp) != NULL)
    {
      Record& record = m_records[m_num_records++];

      char* line_ptr = &(line[0]);
      line_ptr       = strtok(line_ptr, " ");
      strcpy(record.spring_conditions, line_ptr);

      line_ptr = strtok(NULL, ",");
      while (line_ptr != NULL)
      {
        sscanf(line_ptr, "%lu", &(record.sets[record.num_sets++]));
        line_ptr = strtok(NULL, ",");
      }
    }

    fclose(fp);
  }
}

void Day12::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  for (uint32_t i = 0; i < m_num_records; i++)
  {
    Record& record = m_records[i];

    uint32_t num_springs = strlen(record.spring_conditions);
    uint32_t num_unknown = 0;
    for (uint32_t j = 0; j < num_springs; j++)
    {
      if (record.spring_conditions[j] == '?')
        num_unknown++;
    }

    uint32_t num_combinations = pow(2, num_unknown);

    for (uint32_t j = 0; j < num_combinations; j++)
    {
      char potential_record[32];
      for (uint32_t k = 0; k < num_unknown; k++)
      {
        bool is_operational = (j >> ((num_unknown - 1) - k)) & 0x01;
      }
    }
  }
}

void Day12::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}
