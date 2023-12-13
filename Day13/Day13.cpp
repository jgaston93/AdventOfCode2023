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
}

void Day13::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}
