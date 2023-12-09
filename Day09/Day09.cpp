#include <cstdio>
#include <cstring>

#include "Day09.hpp"

using namespace DAY09;

Day09::Day09() : m_report_length(0), m_history_length(0) {}

Day09::~Day09()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day09::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
  memset(m_report, 0, sizeof(m_report));
}

void Day09::Configure(const ConfigurationResource configuration_resource,
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
    char line[512]                  = {0};
    bool history_length_initialized = false;

    // Get history sequence for each variable
    while (fgets(line, sizeof(line), fp) != NULL &&
           return_code == RETURN_CODE_TYPE::NO_ERROR)
    {
      if (m_report_length >= max_report_length)
      {
        return_code = RETURN_CODE_TYPE::MEMORY_EXCEEDED;
      }
      else
      {
        char* line_ptr         = &(line[0]);
        line_ptr               = strtok(line, " ");
        uint32_t value_counter = 0;
        // Get each value in sequence
        while (line_ptr != NULL && return_code == RETURN_CODE_TYPE::NO_ERROR)
        {
          // Ensure report bounds are not exceeded
          if (value_counter >= max_history_length)
          {
            return_code = RETURN_CODE_TYPE::MEMORY_EXCEEDED;
          }
          else
          {
            // Scan value and add to report
            int32_t value = 0;
            sscanf(line_ptr, "%d", &value);
            m_report[m_report_length][value_counter++] = value;

            // Count length of history sequence
            if (!history_length_initialized)
            {
              m_history_length++;
            }
            line_ptr = strtok(NULL, " \n");
          }
        }

        // Only count history sequence length on first pass
        history_length_initialized = true;

        m_report_length++;
      }
    }

    fclose(fp);
  }
}

void Day09::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  // Allocate workspace for calculating and storing values
  int32_t** workspace = new int32_t*[m_history_length];
  for (uint32_t i = 0; i < m_history_length; i++)
  {
    workspace[i] = new int32_t[m_history_length + 2];
    memset(workspace[i], 0, (m_history_length + 2) * sizeof(int32_t));
  }

  int32_t future_prediction_sum = 0;
  int32_t past_prediction_sum   = 0;
  // Evaluate each history sequence
  for (uint32_t i = 0; i < m_report_length; i++)
  {
    // Clean up workspace
    for (uint32_t j = 0; j < m_history_length; j++)
      memset(workspace[j], 0, (m_history_length + 2) * sizeof(int32_t));

    // Add initial history sequence
    memcpy(workspace[0] + 1, m_report[i], m_history_length * sizeof(int32_t));

    // Continue getting steps until all zeros are found
    bool all_zeros         = false;
    uint32_t num_sequences = 0;
    for (uint32_t j = 0; j < m_history_length - 1 && !all_zeros; j++)
    {
      // Get differences and add to next line
      uint32_t non_zero_count = 0;
      for (uint32_t k = 1; k < m_history_length - j; k++)
      {
        workspace[j + 1][k] = workspace[j][k + 1] - workspace[j][k];

        // Find number of non zero steps
        if (workspace[j + 1][k] != 0)
          non_zero_count++;
      }

      // Check if all zeros have been found
      if (non_zero_count == 0)
      {
        all_zeros     = true;
        num_sequences = j;
      }
    }

    // Find future and past values
    for (int32_t j = num_sequences; j >= 0; j--)
    {
      workspace[j][m_history_length - j + 1] =
        workspace[j][(m_history_length - j + 1) - 1] +
        workspace[j + 1][(m_history_length - j + 1) - 1];

      workspace[j][0] = workspace[j][1] - workspace[j + 1][0];
    }

    // Keep sum of all predictions
    future_prediction_sum += workspace[0][m_history_length + 1];
    past_prediction_sum += workspace[0][0];
  }
  printf("Part 1 solution: %d\n", future_prediction_sum);
  printf("Part 2 solution: %d\n", past_prediction_sum);

  // Dispose of workspace
  for (uint32_t i = 0; i < m_history_length; i++)
  {
    delete[] workspace[i];
  }
  delete[] workspace;
}

void Day09::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}