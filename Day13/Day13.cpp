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
      map.num_cols         = line_length - 1;
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

  uint32_t sum = 0;

  for (uint32_t i = 0; i < m_num_maps; i++)
  {
    Map& map = m_maps[i];

    // Check horizontal reflection
    bool full_reflection_found = false;
    for (uint32_t j = 0; j < map.num_rows - 1 && !full_reflection_found; j++)
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
        full_reflection_found           = true;
        uint32_t opposite_index_counter = j + 2;
        for (int32_t x = j - 1;
             x >= 0 && opposite_index_counter < map.num_rows &&
             full_reflection_found;
             x--)
        {
          bool all_match = true;
          for (uint32_t y = 0; y < map.num_cols && all_match; y++)
          {
            if (map.grid[x][y] != map.grid[opposite_index_counter][y])
              all_match = false;
          }
          if (!all_match)
            full_reflection_found = false;
          opposite_index_counter++;
        }

        if (full_reflection_found)
          sum += (j + 1) * 100;
      }
    }

    if (!full_reflection_found)
    {
      // Check vertical reflection
      for (uint32_t j = 0; j < map.num_cols - 1 && !full_reflection_found; j++)
      {
        // Check if two rows match
        bool all_match = true;
        for (uint32_t k = 0; k < map.num_rows && all_match; k++)
        {
          if (map.grid[k][j] != map.grid[k][j + 1])
            all_match = false;
        }

        // Record matching row index
        if (all_match)
        {
          full_reflection_found           = true;
          uint32_t opposite_index_counter = j + 2;
          for (int32_t x = j - 1;
               x >= 0 && opposite_index_counter < map.num_cols &&
               full_reflection_found;
               x--)
          {
            bool all_match = true;
            for (uint32_t y = 0; y < map.num_rows && all_match; y++)
            {
              if (map.grid[y][x] != map.grid[y][opposite_index_counter])
                all_match = false;
            }
            if (!all_match)
              full_reflection_found = false;
            opposite_index_counter++;
          }

          if (full_reflection_found)
            sum += j + 1;
        }
      }
    }
  }
  printf("Part 1 solution: %lu\n", sum);
}

void Day13::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}
