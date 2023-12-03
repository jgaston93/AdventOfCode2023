#include <cstdio>
#include <cstring>

#include "Day03.hpp"

Day03::Day03() : m_nodes(NULL), m_num_rows(0), m_num_columns(0) {}

Day03::~Day03()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day03::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day03::Configure(const ConfigurationResource configuration_resource,
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

    // Determine number of columns
    while (line[m_num_columns] != '\n' && line[m_num_columns] != '\0')
      m_num_columns++;

    // Determine number of rows
    m_num_rows = 1;
    while (fgets(line, sizeof(line), fp) != NULL)
      m_num_rows++;

    fseek(fp, 0, SEEK_SET);

    m_nodes = new Node**[m_num_rows];
    for (unsigned int i = 0; i < m_num_rows; i++)
    {
      m_nodes[i] = new Node*[m_num_columns];
      for (unsigned int j = 0; j < m_num_columns; j++)
      {
        m_nodes[i][j] = NULL;
      }
    }

    unsigned int node_id   = 0;
    unsigned int row_index = 0;

    // Iterate over file line by line
    while (fgets(line, sizeof(line), fp) != NULL)
    {
      unsigned int column_index = 0;
      // Iterate over line character by characters
      char* current_char = &line[0];
      while (*current_char != '\n' && *current_char != '\0')
      {
        Node* node = NULL;
        // Check if number found
        if ('0' <= *current_char && *current_char <= '9')
        {
          // Determine length of number
          unsigned int number_length = 1;
          char* next_char            = current_char + 1;
          while ('0' <= *next_char && *next_char <= '9')
          {
            number_length++;
            next_char++;
          }

          // Build format specifier given length of number
          char format_specifier[8] = {0};
          format_specifier[0]      = '%';
          sprintf(&(format_specifier[1]), "%lu", number_length);
          strncat(format_specifier, "lu", sizeof(format_specifier));

          // Extract number from line
          unsigned int number_value = 0;
          sscanf(current_char, format_specifier, &number_value);

          NumberNode* number_node = new NumberNode(node_id++, number_value);
          node                    = number_node;

          for (unsigned int i = 0; i < number_length; i++)
          {
            m_nodes[row_index][column_index + i] = node;
          }
          column_index += number_length;

          // Update current_char to point to end of number string
          current_char = next_char - 1;
        }
        // Found a symbol
        else if (*current_char != '.')
        {
          SymbolNode* symbol_node = new SymbolNode(node_id++, *current_char);
          node                    = symbol_node;
          m_nodes[row_index][column_index] = node;
          column_index++;
        }
        // Found a period
        else
        {
          EmptyNode* empty_node            = new EmptyNode(node_id++);
          node                             = empty_node;
          m_nodes[row_index][column_index] = node;
          column_index++;
        }
        // Move to next character
        current_char++;
      }
      row_index++;
      memset(line, 0, sizeof(line));
    }
  }
}

void Day03::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  unsigned int part_sum = 0;

  for (unsigned int i = 0; i < m_num_rows; i++)
  {
    for (unsigned int j = 0; j < m_num_columns; j++)
    {
      if (m_nodes[i][j]->type == SYMBOL)
      {
        int top = i - 1;
        if (top < 0)
          top = 0;
        int bottom = i + 1;
        if (bottom >= m_num_rows)
          bottom = m_num_rows - 1;

        int left = j - 1;
        if (left < 0)
          left = 0;
        int right = j + 1;
        if (right >= m_num_columns)
          right = m_num_columns - 1;

        unsigned int num_visited_nodes = 0;
        unsigned int visited_nodes[8]  = {0};

        for (unsigned int k = top; k <= bottom; k++)
        {
          for (unsigned int l = left; l <= right; l++)
          {
            if (!(i == k && j == l) && m_nodes[k][l]->type == NUMBER)
            {
              bool visited = false;
              for (unsigned int m = 0; m < num_visited_nodes && !visited; m++)
              {
                if (m_nodes[k][l]->id == visited_nodes[m])
                  visited = true;
              }
              if (!visited)
              {
                visited_nodes[num_visited_nodes++] = m_nodes[k][l]->id;
                part_sum +=
                  static_cast<NumberNode*>(m_nodes[k][l])->part_number;
              }
            }
          }
        }
      }
    }
  }
  printf("Part 1 solution: %lu\n", part_sum);
}

void Day03::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  m_num_rows    = 0;
  m_num_columns = 0;
  for (unsigned int i = 0; i < m_num_rows; i++)
  {
    for (unsigned int j = 0; j < m_num_columns; j++)
    {
      delete m_nodes[i][j];
    }
    delete[] m_nodes[i];
  }
  delete[] m_nodes;
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}