#include <cstdio>
#include <cstring>

#include "Day05.hpp"

Day05::Day05() : m_num_seeds(0), m_num_mappings(0) {}

Day05::~Day05()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day05::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  memset(m_seeds, 0, sizeof(m_seeds));
  memset(m_mappings, 0, sizeof(m_mappings));
}

void Day05::Configure(const ConfigurationResource configuration_resource,
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
    char line[256] = {0};
    fgets(line, sizeof(line), fp);

    m_num_seeds = 0;

    char* line_ptr = &line[0];
    line_ptr       = strtok(line_ptr, ":");
    line_ptr       = strtok(NULL, " ");
    while (line_ptr != NULL)
    {
      unsigned int seed_number = 0;
      sscanf(line_ptr, "%lu", &seed_number);
      m_seeds[m_num_seeds++] = seed_number;
      line_ptr               = strtok(NULL, " ");
    }

    // Skip empty line
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) != NULL)
    {
      fgets(line, sizeof(line), fp);
      while (line[0] != '\n')
      {
        sscanf(line, "%lu %lu %lu",
               &(m_mappings[m_num_mappings]
                   .ranges[m_mappings[m_num_mappings].num_ranges]
                   .destination_start),
               &(m_mappings[m_num_mappings]
                   .ranges[m_mappings[m_num_mappings].num_ranges]
                   .source_start),
               &(m_mappings[m_num_mappings]
                   .ranges[m_mappings[m_num_mappings].num_ranges]
                   .range));
        m_mappings[m_num_mappings].num_ranges++;

        fgets(line, sizeof(line), fp);
      }

      m_num_mappings++;
    }

    for (unsigned int i = 0; i < m_num_seeds; i++)
    {
      printf("%lu\n", m_seeds[i]);
    }
    printf("\n");

    for (unsigned int i = 0; i < m_num_mappings; i++)
    {
      for (unsigned int j = 0; j < m_mappings[i].num_ranges; j++)
      {
        printf("%lu %lu %lu\n", m_mappings[i].ranges[j].destination_start,
               m_mappings[i].ranges[j].source_start,
               m_mappings[i].ranges[j].range);
      }

      printf("\n");
    }
  }
}

void Day05::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day05::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}