#include <cstdio>
#include <cstring>

#include "Day06.hpp"

using namespace DAY06;

Day06::Day06() : m_num_race(0) {}

Day06::~Day06()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day06::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
  memset(m_races, 0, sizeof(m_races));
}

void Day06::Configure(const ConfigurationResource configuration_resource,
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
    char* line_ptr = &line[0];

    fgets(line, sizeof(line), fp);

    line_ptr = strtok(line_ptr, ":");
    line_ptr = strtok(NULL, " ");

    while (line_ptr != NULL)
    {
      uint32_t time = 0;
      sscanf(line_ptr, "%lu", &time);
      m_races[m_num_race].time = time;
      m_num_race++;
      line_ptr = strtok(NULL, " ");
    }

    fgets(line, sizeof(line), fp);
    line_ptr = &line[0];

    line_ptr         = strtok(line_ptr, ":");
    line_ptr         = strtok(NULL, " ");
    uint32_t counter = 0;
    while (line_ptr != NULL)
    {
      uint32_t distance = 0;
      sscanf(line_ptr, "%lu", &distance);
      m_races[counter].distance = distance;
      counter++;
      line_ptr = strtok(NULL, " ");
    }

    fclose(fp);
  }
}

void Day06::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  m_num_race = 1;

  m_races[0].time     = 47986698;
  m_races[0].distance = 400121310111540;

  uint64_t error_margin = 1;
  for (uint64_t i = 0; i < m_num_race; i++)
  {
    uint64_t num_win = 0;
    for (uint64_t j = 0; j < m_races[i].time; j++)
    {
      uint64_t distance = j * (m_races[i].time - j);
      if (distance > m_races[i].distance)
      {
        num_win++;
      }
    }
    error_margin *= num_win;
  }
  printf("Part 2 solution: %lu\n", error_margin);
}

void Day06::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}