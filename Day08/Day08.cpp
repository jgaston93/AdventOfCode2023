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

    // Get direction list from file
    fgets(line, sizeof(line), fp);
    sscanf(line, "%s", m_directions);

    // Get number of directions
    for (uint32_t i = 0; i < 512 && line[i] != '\n'; i++)
      m_num_directions++;

    // Skip empty line
    fgets(line, sizeof(line), fp);

    // Read each node from file
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

    // Connect nodes
    for (uint32_t i = 0; i < m_num_nodes; i++)
    {
      Node& node_a = m_nodes[i];

      // Check for start nodes
      if (node_a.name[2] == 'A')
      {
        m_start_nodes[m_num_start_nodes++] = &node_a;
      }

      // Find left and right nodes
      bool left_found  = false;
      bool right_found = false;
      for (uint32_t j = 0; j < m_num_nodes && (!left_found || !right_found);
           j++)
      {
        Node& node_b = m_nodes[j];

        // Link left node
        if (!left_found && strcmp(node_a.left_name, node_b.name) == 0)
        {
          node_a.left = &node_b;
          left_found  = true;
        }

        // Link right node
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

  uint64_t num_steps[512] = {0};
  for (uint32_t i = 0; i < m_num_start_nodes; i++)
  {
    uint32_t destination_count      = 0; // Number of times reached Z
    uint32_t destination_count_goal = 1; // Target number of times Z is reached
    uint32_t instruction_count      = 0; // Count number of steps taken
    uint32_t direction_counter      = 0; // Index into direction list
    char current_direction =
      m_directions[direction_counter];     // Get first direction
    Node* current_node = m_start_nodes[i]; // Get start node
    while (destination_count < destination_count_goal)
    {
      // Check for destination
      if (current_node->name[2] == 'Z')
      {
        destination_count++;
      }

      // Move to next node
      if (destination_count < destination_count_goal)
      {
        if (current_direction == 'L')
        {
          current_node = current_node->left;
        }
        else
        {
          current_node = current_node->right;
        }
        // Increase step count
        instruction_count++;

        // Round robin index for direction counter
        direction_counter++;
        if (direction_counter >= m_num_directions)
          direction_counter = 0;
        current_direction = m_directions[direction_counter];
      }
    }
    // Save number of steps taken to destination
    num_steps[i] = instruction_count;
  }

  // Initialize step counter list with initial step sizes
  uint64_t step_counter[512] = {0};
  for (uint32_t i = 0; i < m_num_start_nodes; i++)
    step_counter[i] = num_steps[i];

  // Look for LCM
  bool destination_found = false;
  while (!destination_found)
  {
    // Find minimum value in step counter list
    uint64_t min_value       = 0xFFFFFFFFFFFFFFFF;
    uint32_t min_value_index = 0;
    for (uint32_t i = 0; i < m_num_start_nodes; i++)
    {
      if (step_counter[i] < min_value)
      {
        min_value       = step_counter[i];
        min_value_index = i;
      }
    }

    // Increment minimum value
    step_counter[min_value_index] += num_steps[min_value_index];

    // Check if LCM found
    bool all_matches = true;
    for (uint32_t i = 0; i < m_num_start_nodes - 1 && all_matches; i++)
    {
      if (step_counter[i] != step_counter[i + 1])
        all_matches = false;
    }
    if (all_matches)
      destination_found = true;
  }
  printf("Part 2 solution: %llu\n", step_counter[0]);
}

void Day08::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}