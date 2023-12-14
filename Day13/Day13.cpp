#include <cstdio>
#include <cstring>

#include "Day13.hpp"

using namespace DAY13;

Day13::Day13() : m_num_maps(0) {}

Day13::~Day13()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day13::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day13::Configure(const ConfigurationResource configuration_resource,
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
      Map& map = m_maps[m_num_maps++];

      uint32_t line_length = strlen(line);
      map.num_cols         = line_length;
      while (line_length > 1 && !feof(fp))
      {
        if (line[line_length - 1] == '\n')
          line[line_length - 1] = '\0';
        strcpy(map.grid[map.num_rows++], line);
        fgets(line, sizeof(line), fp);
        line_length = strlen(line);
      }
      if (feof(fp))
      {
        if (line[line_length - 1] == '\n')
          line[line_length - 1] = '\0';
        strcpy(map.grid[map.num_rows++], line);
      }
    }

    fclose(fp);
  }
}

void Day13::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  for (uint32_t i = 0; i < m_num_maps; i++)
  {
    Map& map = m_maps[i];

    // Check horizontal reflection
    bool horizontal_reflection_found    = false;
    int32_t horizontal_reflection_index = 0;
    for (uint32_t j = 0; j < map.num_rows - 1 && !horizontal_reflection_found;
         j++)
    {
      // Check if two rows match
      bool all_match = true;
      for (uint32_t k = 0; k < map.num_cols && all_match; k++)
      {
        if (map.grid[j][k] != map.grid[j + 1][k])
          all_match = false;
      }

      // Record matching row index
      if (all_match)
      {
        horizontal_reflection_found = true;
        horizontal_reflection_index = j;
      }
    }

    // Check for full reflection
    if (horizontal_reflection_found)
    {
      bool full_reflection_found = true;
      for (int32_t j = horizontal_reflection_index - 1;
           j >= 0 && map.num_rows - j < map.num_rows && full_reflection_found;
           j--)
      {
        bool all_match = true;
        for (uint32_t k = 0; k < map.num_cols && all_match; k++)
        {
          if (map.grid[j][k] != map.grid[map.num_rows - j][k])
            all_match = false;
        }
        if (!all_match)
          full_reflection_found = false;
      }

      if (full_reflection_found)
      {
        printf("%lu\n", horizontal_reflection_index);
      }
      else
        horizontal_reflection_found = false;
    }

    if (!horizontal_reflection_found)
    {
      // Check vertical reflection
      bool vertical_reflection_found    = false;
      int32_t vertical_reflection_index = 0;
      for (uint32_t j = 0; j < map.num_rows - 1 && !vertical_reflection_found;
           j++)
      {
        // Check if two rows match
        bool all_match = true;
        for (uint32_t k = 0; k < map.num_cols && all_match; k++)
        {
          if (map.grid[j][k] != map.grid[j + 1][k])
            all_match = false;
        }

        // Record matching row index
        if (all_match)
        {
          vertical_reflection_found = true;
          vertical_reflection_index = j;
        }
      }

      // Check for full reflection
      if (vertical_reflection_found)
      {
        bool full_reflection_found = true;
        for (int32_t j = vertical_reflection_index - 1;
             j >= 0 && map.num_rows - j < map.num_rows && full_reflection_found;
             j--)
        {
          bool all_match = true;
          for (uint32_t k = 0; k < map.num_cols && all_match; k++)
          {
            if (map.grid[j][k] != map.grid[map.num_rows - j][k])
              all_match = false;
          }
          if (!all_match)
            full_reflection_found = false;
        }

        if (full_reflection_found)
        {
          printf("%lu\n", vertical_reflection_index);
        }
        else
          vertical_reflection_found = false;
      }
    }
  }
}

void Day13::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}
