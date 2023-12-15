#include <cstdio>
#include <cstring>

#include "Day14.hpp"

using namespace DAY14;

Day14::Day14() : m_current_dish(0), m_dish_size(0) {}

Day14::~Day14()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day14::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day14::Configure(const ConfigurationResource configuration_resource,
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

    uint32_t i = 0;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
      if (m_dish_size == 0)
        m_dish_size = strlen(line) - 1;

      if (line[m_dish_size] == '\n')
        line[m_dish_size] = '\0';

      strcpy(m_dish[m_current_dish][i++], line);
    }

    fclose(fp);
  }
}

void Day14::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  // Spin cycle
  uint32_t load_list[1000] = {0};
  uint32_t num_cycles      = 1e3;
  uint32_t cycle_length    = 4;
  for (uint32_t i = 0; i < num_cycles; i++)
  {
    for (uint32_t j = 0; j < cycle_length; j++)
    {
      // Tile dish
      for (uint32_t x = 0; x < m_dish_size; x++)
      {
        uint32_t new_position = 0;
        for (uint32_t y = 0; y < m_dish_size; y++)
        {
          if (m_dish[m_current_dish][y][x] == 'O')
          {
            char swap = m_dish[m_current_dish][y][x];
            m_dish[m_current_dish][y][x] =
              m_dish[m_current_dish][new_position][x];
            m_dish[m_current_dish][new_position][x] = swap;
            new_position++;
          }
          else if (m_dish[m_current_dish][y][x] == '#')
            new_position = y + 1;
        }
      }

      // Rotate dish
      uint32_t next_dish = m_current_dish + 1;
      if (next_dish >= MAX_NUM_DISH)
        next_dish = 0;

      for (uint32_t y = 0; y < m_dish_size; y++)
      {
        for (uint32_t x = 0; x < m_dish_size; x++)
        {
          m_dish[next_dish][x][(m_dish_size - 1) - y] =
            m_dish[m_current_dish][y][x];
        }
      }
      m_current_dish = next_dish;
    }

    // Calculate load
    uint32_t load_sum = 0;
    for (uint32_t x = 0; x < m_dish_size; x++)
    {
      for (uint32_t y = 0; y < m_dish_size; y++)
      {
        if (m_dish[m_current_dish][y][x] == 'O')
        {
          load_sum += m_dish_size - y;
        }
      }
    }
    load_list[i] = load_sum;
  }

  uint32_t num_loads = 1000;
  for (uint32_t i = / 2; i <)

    // Calculate load
    uint32_t load_sum = 0;
  for (uint32_t x = 0; x < m_dish_size; x++)
  {
    for (uint32_t y = 0; y < m_dish_size; y++)
    {
      if (m_dish[m_current_dish][y][x] == 'O')
      {
        load_sum += m_dish_size - y;
      }
    }
  }

  printf("Part 1 solution: %lu\n", load_sum);
}

void Day14::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}
