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

  uint32_t num_valid_permutations_sum = 0;

  for (uint32_t i = 0; i < m_num_records; i++)
  {
    Record& record = m_records[i];

    uint32_t num_springs = strlen(record.spring_conditions);

    // Count number of unknown conditions and track indices
    uint32_t num_unknown         = 0;
    uint32_t unknown_indices[32] = {0};
    for (uint32_t j = 0; j < num_springs; j++)
    {
      if (record.spring_conditions[j] == '?')
        unknown_indices[num_unknown++] = j;
    }

    // Get number of permutations based number of unknown conditions
    uint32_t num_permutations = pow(2, num_unknown);

    uint32_t num_valid_permutations = 0;

    // Check each permutation
    for (uint32_t j = 0; j < num_permutations; j++)
    {
      // Fill potential record with current conditions
      char potential_record[32] = {0};
      for (uint32_t k = 0; k < num_springs; k++)
        potential_record[k] = record.spring_conditions[k];

      // Fill unknowns based on current permutation
      for (uint32_t k = 0; k < num_unknown; k++)
      {
        bool is_operational = (j >> ((num_unknown - 1) - k)) & 0x01;
        if (is_operational)
          potential_record[unknown_indices[k]] = '.';
        else
          potential_record[unknown_indices[k]] = '#';
      }

      // Check if record is valid
      uint32_t potential_sets[16] = {0};
      uint32_t num_potential_sets = 0;

      // Find number and count of contiguous sets
      char* cond_ptr = &(potential_record[0]);
      cond_ptr       = strtok(cond_ptr, ".");
      while (cond_ptr != NULL)
      {
        uint32_t len = strlen(cond_ptr);
        for (uint32_t k = 0; k < len; k++)
          potential_sets[num_potential_sets]++;
        num_potential_sets++;
        cond_ptr = strtok(NULL, ".");
      }

      // Check if number of sets match the valid amount
      bool permutation_valid = true;
      if (num_potential_sets != record.num_sets)
      {
        permutation_valid = false;
      }

      for (uint32_t k = 0; k < num_potential_sets && permutation_valid; k++)
      {
        if (potential_sets[k] != record.sets[k])
          permutation_valid = false;
      }

      if (permutation_valid)
        num_valid_permutations++;
    }
    num_valid_permutations_sum += num_valid_permutations;
  }

  printf("Part 1 solution: %lu\n", num_valid_permutations_sum);
}

void Day12::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}
