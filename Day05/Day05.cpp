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
      while (line[0] != '\n' && !feof(fp))
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
      if (feof(fp))
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
      }

      m_num_mappings++;
    }
  }
}

void Day05::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  for (unsigned int i = 0; i < m_num_seeds; i++)
  {
    for (unsigned int j = 0; j < m_num_mappings; j++)
    {
      bool mapping_found = false;
      for (unsigned int k = 0; k < m_mappings[j].num_ranges && !mapping_found;
           k++)
      {
        if (m_mappings[j].ranges[k].source_start <= m_seeds[i] &&
            m_seeds[i] <= m_mappings[j].ranges[k].source_start +
                            m_mappings[j].ranges[k].range)
        {
          m_seeds[i] += m_mappings[j].ranges[k].destination_start -
                        m_mappings[j].ranges[k].source_start;
          mapping_found = true;
        }
      }
    }
  }

  unsigned int lowest_location_number = 0xFFFFFFFF;
  for (unsigned int i = 0; i < m_num_seeds; i++)
  {
    if (m_seeds[i] < lowest_location_number)
      lowest_location_number = m_seeds[i];
  }

  printf("Part 1 solution: %lu\n", lowest_location_number);
}

void Day05::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}