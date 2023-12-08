#include <cstdio>
#include <cstring>

#include "Day08.hpp"

using namespace DAY08;

Day08::Day08() : m_num_nodes(0), m_num_start_nodes(0), m_num_directions(0) {}

Day08::~Day08()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day08::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
  memset(m_nodes, 0, sizeof(m_nodes));
  memset(m_start_nodes, 0, sizeof(m_start_nodes));
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
    char line[512] = {0};

    fgets(line, sizeof(line), fp);
    sscanf(line, "%s", m_directions);

    for (unsigned int i = 0; i < 512 && line[i] != '\n'; i++)
      m_num_directions++;

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) != NULL)
    {
      Node& node = m_nodes[m_num_nodes];
      sscanf(line, "%c%c%c = (%c%c%c, %c%c%c)", &(node.name[0]),
             &(node.name[1]), &(node.name[2]), &(node.left_name[0]),
             &(node.left_name[1]), &(node.left_name[2]), &(node.right_name[0]),
             &(node.right_name[1]), &(node.right_name[2]));

      node.name[3]       = '\0';
      node.left_name[3]  = '\0';
      node.right_name[3] = '\0';
      m_num_nodes++;
    }

    for (unsigned int i = 0; i < m_num_nodes; i++)
    {
      Node& node_a = m_nodes[i];

      if (node_a.name[2] == 'A')
      {
        m_start_nodes[m_num_start_nodes++] = &node_a;
      }

      bool left_found  = false;
      bool right_found = false;
      for (unsigned int j = 0; j < m_num_nodes && (!left_found || !right_found);
           j++)
      {
        Node& node_b = m_nodes[j];

        if (!left_found && strcmp(node_a.left_name, node_b.name) == 0)
        {
          node_a.left = &node_b;
          left_found  = true;
        }

        if (!right_found && strcmp(node_a.right_name, node_b.name) == 0)
        {
          node_a.right = &node_b;
          right_found  = true;
        }
      }
    }

    fclose(fp);
  }
}

void Day08::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  bool destination_found         = false;
  unsigned int instruction_count = 0;
  unsigned int direction_counter = 0;
  char current_direction         = m_directions[direction_counter];

  while (!destination_found)
  {
    unsigned int z_counter = 0;
    for (unsigned int i = 0; i < m_num_start_nodes; i++)
    {
      if (m_start_nodes[i]->name[2] == 'Z')
      {
        z_counter++;
      }
    }

    if (z_counter == m_num_start_nodes)
      destination_found = true;

    if (!destination_found)
    {
      for (unsigned int i = 0; i < m_num_start_nodes; i++)
      {
        if (current_direction == 'L')
        {
          m_start_nodes[i] = m_start_nodes[i]->left;
        }
        else
        {
          m_start_nodes[i] = m_start_nodes[i]->right;
        }
      }
      instruction_count++;
      direction_counter++;
      if (direction_counter >= m_num_directions)
        direction_counter = 0;
      current_direction = m_directions[direction_counter];
    }
  }

  printf("Part 2 solution: %lu\n", instruction_count);
}

void Day08::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}