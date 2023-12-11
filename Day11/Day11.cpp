#include <cstdio>
#include <cstring>

#include "Day11.hpp"

using namespace DAY11;

Day11::Day11() : m_num_rows(0), m_num_cols(0), m_num_galaxies(0) {}

Day11::~Day11()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day11::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day11::Configure(const ConfigurationResource configuration_resource,
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

    bool num_cols_initialized = false;

    // Iterate over each row
    while (fgets(line, sizeof(line), fp) != NULL &&
           return_code == RETURN_CODE_TYPE::NO_ERROR)
    {

      // On first pass find number of columns
      if (!num_cols_initialized)
      {
        for (uint32_t i = 0;
             line[i] != '\n' && return_code == RETURN_CODE_TYPE::NO_ERROR; i++)
        {
          m_num_cols++;
          if (m_num_cols > MAX_NUM_COLS)
            return_code = RETURN_CODE_TYPE::MEMORY_EXCEEDED;
        }
        num_cols_initialized = true;
      }

      // Iterate over each column to determine type
      for (uint32_t i = 0;
           i < m_num_cols && return_code == RETURN_CODE_TYPE::NO_ERROR; i++)
      {
        Tile& tile = m_space[m_num_rows][i];
        switch (line[i])
        {
        case '.':
          tile.type = Space;
          break;
        case '#':
          tile.type = Galaxy;
          tile.id   = m_num_galaxies++; // Assign id to each galaxy
          break;
        }
      }

      m_num_rows++;
      if (m_num_rows > MAX_NUM_ROWS)
        return_code = RETURN_CODE_TYPE::MEMORY_EXCEEDED;
    }

    // Create memory to store galaxy cooridnates
    m_galaxy_coordinate_list = new Position[m_num_galaxies];

    // Keep track of number of galaxies in each row and column
    // to determine if expansion has occured
    uint32_t row_galaxy_count[MAX_NUM_ROWS] = {0};
    uint32_t col_galaxy_count[MAX_NUM_COLS] = {0};
    for (uint32_t i = 0; i < m_num_rows; i++)
    {
      for (uint32_t j = 0; j < m_num_cols; j++)
      {
        if (m_space[i][j].type == Galaxy)
        {
          // Increment galaxy count
          row_galaxy_count[i]++;
          col_galaxy_count[j]++;
          // Add coordinates to coordinate list
          m_galaxy_coordinate_list[i].x = i;
          m_galaxy_coordinate_list[i].y = j;
        }
      }
    }

    // Update distances based on empty space found
    for (uint32_t i = 0; i < m_num_rows; i++)
    {
      for (uint32_t j = 0; j < m_num_cols; j++)
      {
        if (row_galaxy_count[i] == 0 || col_galaxy_count[j] == 0)
          m_space[i][j].distance *= 2;
      }
    }

    fclose(fp);
  }
}

void Day11::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  for (uint32_t i = 0; i < m_num_galaxies - 1; i++)
  {
    for (uint32_t j = i + 1; j < m_num_galaxies; j++)
    {
      Position start_position = m_galaxy_coordinate_list[i];
      Position end_position   = m_galaxy_coordinate_list[j];
    }
  }
}

void Day11::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}
