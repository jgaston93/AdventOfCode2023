#include <cstdio>
#include <cstring>

#include "Day08.hpp"

using namespace DAY08;

Day08::Day08() : m_num_nodes(0), m_num_directions(0) {}

Day08::~Day08()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day08::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
  memset(m_nodes, 0, sizeof(m_nodes));
  memset(m_directions, 0, sizeof(m_directions));
}

void Day08::Configure(const ConfigurationResource configuration_resource,
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
    sscanf(line, "%s", m_directions);

    for (unsigned int i = 0; i < 256 && line[i] != '\n'; i++)
      m_num_directions++;

    printf("%lu %s\n", m_num_directions, m_directions);

    fclose(fp);
  }
}

void Day08::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day08::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}