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
                   .length));
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
                   .length));
        m_mappings[m_num_mappings].num_ranges++;
      }

      m_num_mappings++;
    }
    fclose(fp);
  }
}

void Day05::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  const unsigned int max_num_seed_ranges = 1024;
  unsigned int num_seed_ranges           = 0;
  struct SeedRange seed_ranges[max_num_seed_ranges];
  for (unsigned int i = 0; i < m_num_seeds; i += 2)
  {
    seed_ranges[num_seed_ranges].start  = m_seeds[i];
    seed_ranges[num_seed_ranges].length = m_seeds[i + 1];
    num_seed_ranges++;
  }

  for (unsigned int i = 0; i < m_num_mappings; i++)
  {
    for (unsigned int j = 0; j < num_seed_ranges; j++)
    {
      SeedRange& seed_range = seed_ranges[j];
      bool mapping_found    = false;
      for (unsigned int k = 0; k < m_mappings[i].num_ranges && !mapping_found;
           k++)
      {
        MappingRange mapping_range = m_mappings[i].ranges[k];

        // Check for collision
        if (seed_range.start <
              (mapping_range.source_start + mapping_range.length) &&
            (seed_range.start + seed_range.length) > mapping_range.source_start)
        {
          // Check left for non overlap
          if (seed_range.start < mapping_range.source_start)
          {
            // Add non overlap to end of list
            seed_ranges[num_seed_ranges].start = seed_range.start;
            seed_ranges[num_seed_ranges].length =
              mapping_range.source_start - seed_range.start;
            num_seed_ranges++;

            // Update current seed range
            seed_range.length -= mapping_range.source_start - seed_range.start;
            seed_range.start = mapping_range.source_start;
          }
          // Check right for non overlap
          if ((seed_range.start + seed_range.length) >
              (mapping_range.source_start + mapping_range.length))
          {
            // Add non overlap to end of list
            seed_ranges[num_seed_ranges].start =
              (mapping_range.source_start + mapping_range.length);
            seed_ranges[num_seed_ranges].length =
              (seed_range.start + seed_range.length) -
              (mapping_range.source_start + mapping_range.length);
            num_seed_ranges++;

            // Update current seed range
            seed_range.length -=
              (seed_range.start + seed_range.length) -
              (mapping_range.source_start + mapping_range.length);
          }

          seed_range.start +=
            mapping_range.destination_start - mapping_range.source_start;
          mapping_found = true;
        }
      }
    }
  }

  unsigned int lowest_location_number = 0xFFFFFFFF;
  for (unsigned int i = 0; i < num_seed_ranges; i++)
  {
    if (seed_ranges[i].start < lowest_location_number)
      lowest_location_number = seed_ranges[i].start;
  }

  printf("Part 2 solution: %lu\n", lowest_location_number);
}

void Day05::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}