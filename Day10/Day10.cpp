#include <cstdio>
#include <cstring>
#include <queue>

#include "Day10.hpp"

using namespace DAY10;

Day10::Day10() : m_num_rows(0), m_num_cols(0) {}

Day10::~Day10()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day10::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day10::Configure(const ConfigurationResource configuration_resource,
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
        Tile& tile = m_tiles[m_num_rows][i];
        switch (line[i])
        {
        case '|':
          tile.type = Vertical;
          break;
        case '-':
          tile.type = Horizontal;
          break;
        case 'L':
          tile.type = NorthAndEast;
          break;
        case 'J':
          tile.type = NorthAndWest;
          break;
        case '7':
          tile.type = SouthAndWest;
          break;
        case 'F':
          tile.type = SouthAndEast;
          break;
        case '.':
          tile.type = Ground;
          break;
        case 'S':
          tile.type    = Start;
          m_start_tile = &tile;
          break;
        }
      }

      m_num_rows++;
      if (m_num_rows > MAX_NUM_ROWS)
        return_code = RETURN_CODE_TYPE::MEMORY_EXCEEDED;
    }

    // Make connections among tiles
    for (int32_t i = 0;
         i < m_num_rows && return_code == RETURN_CODE_TYPE::NO_ERROR; i++)
    {
      for (int32_t j = 0;
           j < m_num_cols && return_code == RETURN_CODE_TYPE::NO_ERROR; j++)
      {
        Tile& tile = m_tiles[i][j];

        if (tile.type == Vertical)
        {
          MakeNorthConnection(i, j, return_code);
          MakeSouthConnection(i, j, return_code);
          if (return_code != RETURN_CODE_TYPE::NO_ERROR)
            printf("Error making connection on tile %d %d\n", i, j);
        }
        else if (tile.type == Horizontal)
        {
          MakeEastConnection(i, j, return_code);
          MakeWestConnection(i, j, return_code);
          if (return_code != RETURN_CODE_TYPE::NO_ERROR)
            printf("Error making connection on tile %d %d\n", i, j);
        }
        else if (tile.type == NorthAndEast)
        {
          MakeNorthConnection(i, j, return_code);
          MakeEastConnection(i, j, return_code);
          if (return_code != RETURN_CODE_TYPE::NO_ERROR)
            printf("Error making connection on tile %d %d\n", i, j);
        }
        else if (tile.type == NorthAndWest)
        {
          MakeNorthConnection(i, j, return_code);
          MakeWestConnection(i, j, return_code);
          if (return_code != RETURN_CODE_TYPE::NO_ERROR)
            printf("Error making connection on tile %d %d\n", i, j);
        }
        else if (tile.type == SouthAndWest)
        {
          MakeSouthConnection(i, j, return_code);
          MakeWestConnection(i, j, return_code);
          if (return_code != RETURN_CODE_TYPE::NO_ERROR)
            printf("Error making connection on tile %d %d\n", i, j);
        }
        else if (tile.type == SouthAndEast)
        {
          MakeSouthConnection(i, j, return_code);
          MakeEastConnection(i, j, return_code);
          if (return_code != RETURN_CODE_TYPE::NO_ERROR)
            printf("Error making connection on tile %d %d\n", i, j);
        }
        else if (tile.type == Start)
        {
          MakeNorthConnection(i, j, return_code);
          MakeSouthConnection(i, j, return_code);
          MakeEastConnection(i, j, return_code);
          MakeWestConnection(i, j, return_code);
          if (return_code != RETURN_CODE_TYPE::NO_ERROR)
            printf("Error making connection on tile %d %d\n", i, j);
        }
      }
    }

    fclose(fp);
  }
}

void Day10::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  // Find max distnce
  uint32_t max_distance = 0;

  // BFS
  std::queue<Tile*> q;

  m_start_tile->distance = 0;
  q.push(m_start_tile);

  while (!q.empty())
  {
    Tile* tile = q.front();
    q.pop();
    tile->visited = true;
    for (uint32_t i = 0; i < tile->num_connected_tiles; i++)
    {
      if (!(tile->connected_tiles[i]->visited))
      {
        uint32_t distance = tile->distance + 1;
        if (distance > max_distance)
          max_distance = distance;
        tile->connected_tiles[i]->distance = distance;
        q.push(tile->connected_tiles[i]);
      }
    }
  }
  printf("Part 1 solution: %lu\n", max_distance);
}

void Day10::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day10::MakeNorthConnection(int32_t row_index, int32_t col_index,
                                RETURN_CODE_TYPE::Value& return_code)
{
  if (row_index - 1 >= 0)
  {
    Tile& tile       = m_tiles[row_index][col_index];
    Tile& north_tile = m_tiles[row_index - 1][col_index];
    if (north_tile.type == Vertical || north_tile.type == SouthAndEast ||
        north_tile.type == SouthAndWest)
    {
      if (tile.num_connected_tiles < MAX_NUM_CONNECTED_TILES)
        tile.connected_tiles[tile.num_connected_tiles++] = &north_tile;
      else
        return_code = RETURN_CODE_TYPE::MEMORY_EXCEEDED;
    }
  }
}

void Day10::MakeSouthConnection(int32_t row_index, int32_t col_index,
                                RETURN_CODE_TYPE::Value& return_code)
{
  if (row_index + 1 < m_num_rows)
  {
    Tile& tile       = m_tiles[row_index][col_index];
    Tile& south_tile = m_tiles[row_index + 1][col_index];
    if (south_tile.type == Vertical || south_tile.type == NorthAndEast ||
        south_tile.type == NorthAndWest)
    {
      if (tile.num_connected_tiles < MAX_NUM_CONNECTED_TILES)
        tile.connected_tiles[tile.num_connected_tiles++] = &south_tile;
      else
        return_code = RETURN_CODE_TYPE::MEMORY_EXCEEDED;
    }
  }
}

void Day10::MakeEastConnection(int32_t row_index, int32_t col_index,
                               RETURN_CODE_TYPE::Value& return_code)
{
  if (col_index + 1 < m_num_cols)
  {
    Tile& tile      = m_tiles[row_index][col_index];
    Tile& east_tile = m_tiles[row_index][col_index + 1];
    if (east_tile.type == Horizontal || east_tile.type == NorthAndWest ||
        east_tile.type == SouthAndWest)
    {
      if (tile.num_connected_tiles < MAX_NUM_CONNECTED_TILES)
        tile.connected_tiles[tile.num_connected_tiles++] = &east_tile;
      else
        return_code = RETURN_CODE_TYPE::MEMORY_EXCEEDED;
    }
  }
}

void Day10::MakeWestConnection(int32_t row_index, int32_t col_index,
                               RETURN_CODE_TYPE::Value& return_code)
{
  if (col_index - 1 >= 0)
  {
    Tile& tile      = m_tiles[row_index][col_index];
    Tile& west_tile = m_tiles[row_index][col_index - 1];
    if (west_tile.type == Horizontal || west_tile.type == NorthAndEast ||
        west_tile.type == SouthAndEast)
    {
      if (tile.num_connected_tiles < MAX_NUM_CONNECTED_TILES)
        tile.connected_tiles[tile.num_connected_tiles++] = &west_tile;
      else
        return_code = RETURN_CODE_TYPE::MEMORY_EXCEEDED;
    }
  }
}
