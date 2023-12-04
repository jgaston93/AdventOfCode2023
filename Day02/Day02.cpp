#include <cstdio>
#include <cstring>

#include "Day02.hpp"

Day02::Day02() : m_num_games(0), m_games(NULL) {}

Day02::~Day02()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day02::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day02::Configure(const ConfigurationResource configuration_resource,
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
    // Get total number of games to allocate memory for games
    char previous_char = 0;
    for (char current_char = fgetc(fp); current_char != EOF;
         current_char      = fgetc(fp))
    {
      // Count number of new line characters
      if (current_char == '\n')
        m_num_games += 1;
      previous_char = current_char;
    }

    // Account for files not ending with new line
    if (previous_char != '\n')
      m_num_games += 1;

    // Allocate memory for games
    m_games = new Game[m_num_games];

    // Reset to beginning of file
    fseek(fp, 0, SEEK_SET);

    // Parse each line for game information
    char line[256] = {0};
    for (unsigned int i = 0; i < m_num_games; i++)
    {
      // Clear buffer and get line
      memset(line, 0, sizeof(line));
      fgets(line, sizeof(line), fp);

      // Get game ID;
      unsigned int game_id = 0;
      sscanf(line, "Game %lu:", &game_id);
      m_games[i].id = game_id;

      // Get number of sets per game
      m_games[i].num_sets = 1;
      for (unsigned int j = 0; j < sizeof(line); j++)
      {
        // Count number of semicolons
        if (line[j] == ';')
          m_games[i].num_sets += 1;
        else if (line[j] == '\0')
          break;
      }

      // Allocate memory for sets for game
      m_games[i].sets = new Set[m_games[i].num_sets];

      // Strip game header info
      char* substring = line;
      while (substring[0] != ':')
        substring += 1;
      substring += 1;

      unsigned int set_index = 0;

      // Iterate over each set
      substring = strtok(substring, ";\n");
      while (substring != NULL)
      {
        char set_info[256] = {0};
        char* set_info_ptr = &set_info[0];
        strcpy(set_info, substring);

        // Iterate over each value in set
        set_info_ptr = strtok(set_info_ptr, ",");
        while (set_info_ptr != NULL)
        {
          // Get number and color
          unsigned int number = 0;
          char color[32]      = {0};
          sscanf(set_info_ptr, "%lu %s", &number, color);

          // Update number for each color
          if (strcmp(color, "red") == 0)
          {
            m_games[i].sets[set_index].num_red += number;
          }
          else if (strcmp(color, "green") == 0)
          {
            m_games[i].sets[set_index].num_green += number;
          }
          else if (strcmp(color, "blue") == 0)
          {
            m_games[i].sets[set_index].num_blue += number;
          }

          set_info_ptr = strtok(NULL, ",");
        }

        // move substring to next set
        unsigned int set_info_length = strlen(substring);
        substring += set_info_length + 1;

        substring = strtok(substring, ";\n");

        set_index++;
      }
    }
    fclose(fp);
  }
}

void Day02::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  // Maximum number of cubes loaded
  unsigned int max_num_red   = 12;
  unsigned int max_num_green = 13;
  unsigned int max_num_blue  = 14;

  // Puzzle answers
  unsigned int valid_game_sum = 0;
  unsigned int power_sum      = 0;

  for (unsigned int i = 0; i < m_num_games; i++)
  {
    // Check if game is valid for max colors
    bool is_game_valid = true;

    // Tracking fewest colors for valid game
    unsigned int fewest_red   = 0;
    unsigned int fewest_blue  = 0;
    unsigned int fewest_green = 0;

    // Check each set in each game
    for (unsigned int j = 0; j < m_games[i].num_sets; j++)
    {
      // Determine if number of colors exceed maximum
      if (m_games[i].sets[j].num_red > max_num_red ||
          m_games[i].sets[j].num_green > max_num_green ||
          m_games[i].sets[j].num_blue > max_num_blue)
        is_game_valid = false;

      // Track fewest colors needed
      if (m_games[i].sets[j].num_red > fewest_red)
        fewest_red = m_games[i].sets[j].num_red;
      if (m_games[i].sets[j].num_green > fewest_green)
        fewest_green = m_games[i].sets[j].num_green;
      if (m_games[i].sets[j].num_blue > fewest_blue)
        fewest_blue = m_games[i].sets[j].num_blue;
    }

    // Update sum for part 1
    if (is_game_valid)
      valid_game_sum += m_games[i].id;

    // Update sum for part 2
    power_sum += (fewest_red * fewest_green * fewest_blue);
  }

  printf("Part 1 Solution: %lu\n", valid_game_sum);
  printf("Part 2 Solution: %lu\n", power_sum);
}

void Day02::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  for (unsigned int i = 0; i < m_num_games; i++)
  {
    for (unsigned int j = 0; j < m_games[i].num_sets; j++)
    {
      m_games[i].num_sets = 0;
      delete[] m_games[i].sets;
    }
  }
  m_num_games = 0;
  delete[] m_games;
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}