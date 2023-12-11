#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>

#include "Day10.hpp"

using namespace DAY10;

// wchar_t TileTypeString[9] = L"║═╚╝╗╔░█";
char TileTypeCharacters[9] = "|-LJ7F.S";

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
          if (m_num_cols > MAX_NUM_COLS - 2)
            return_code = RETURN_CODE_TYPE::MEMORY_EXCEEDED;
        }
        num_cols_initialized = true;
      }

      // Iterate over each column to determine type
      for (uint32_t i = 0;
           i < m_num_cols && return_code == RETURN_CODE_TYPE::NO_ERROR; i++)
      {
        Tile& tile = m_tiles[m_num_rows + 1][i + 1];
        tile.loc_y = m_num_rows;
        tile.loc_x = i;
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
      if (m_num_rows > MAX_NUM_ROWS - 2)
        return_code = RETURN_CODE_TYPE::MEMORY_EXCEEDED;
    }

    m_num_rows += 2;
    m_num_cols += 2;

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
    tile->visited   = true;
    tile->main_loop = true;

    uint32_t distance   = tile->distance + 1;
    bool new_tile_found = false;

    if (tile->north_tile != NULL && !(tile->north_tile->visited))
    {
      new_tile_found             = true;
      tile->north_tile->distance = distance;
      q.push(tile->north_tile);
    }
    if (tile->south_tile != NULL && !(tile->south_tile->visited))
    {
      new_tile_found             = true;
      tile->south_tile->distance = distance;
      q.push(tile->south_tile);
    }
    if (tile->east_tile != NULL && !(tile->east_tile->visited))
    {
      new_tile_found            = true;
      tile->east_tile->distance = distance;
      q.push(tile->east_tile);
    }
    if (tile->west_tile != NULL && !(tile->west_tile->visited))
    {
      new_tile_found            = true;
      tile->west_tile->distance = distance;
      q.push(tile->west_tile);
    }

    if (new_tile_found && distance > max_distance)
      max_distance = distance;
  }

  printf("Part 1 solution: %lu\n", max_distance);

  for (uint32_t i = 0; i < m_num_rows; i++)
  {
    for (uint32_t j = 0; j < m_num_cols; j++)
    {
      // Clean up tiles not in main loop
      if (!m_tiles[i][j].main_loop)
      {
        m_tiles[i][j].type       = Ground;
        m_tiles[i][j].north_tile = NULL;
        m_tiles[i][j].south_tile = NULL;
        m_tiles[i][j].east_tile  = NULL;
        m_tiles[i][j].west_tile  = NULL;
        printf(".");
      }
      // Reset main loop tiles for another loop
      else
      {
        m_tiles[i][j].visited = false;
        printf("%c", TileTypeCharacters[m_tiles[i][j].type]);
      }
    }
    printf("\n");
  }

  // std::stack<Tile*> s;
  // s.push(m_start_tile);

  // while (!s.empty())
  // {
  //   Tile* tile = s.top();
  //   s.pop();
  //   tile->visited = true;

  //   uint32_t distance   = tile->distance + 1;
  //   bool new_tile_found = false;

  //   if (tile->north_tile != NULL && !(tile->north_tile->visited))
  //   {
  //     new_tile_found             = true;
  //     tile->north_tile->distance = distance;
  //     q.push(tile->north_tile);
  //   }
  //   if (tile->south_tile != NULL && !(tile->south_tile->visited))
  //   {
  //     new_tile_found             = true;
  //     tile->south_tile->distance = distance;
  //     q.push(tile->south_tile);
  //   }
  //   if (tile->east_tile != NULL && !(tile->east_tile->visited))
  //   {
  //     new_tile_found            = true;
  //     tile->east_tile->distance = distance;
  //     q.push(tile->east_tile);
  //   }
  //   if (tile->west_tile != NULL && !(tile->west_tile->visited))
  //   {
  //     new_tile_found            = true;
  //     tile->west_tile->distance = distance;
  //     q.push(tile->west_tile);
  //   }

  //   if (new_tile_found && distance > max_distance)
  //     max_distance = distance;
  // }
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
      tile.north_tile = &north_tile;
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
      tile.south_tile = &south_tile;
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
      tile.east_tile = &east_tile;
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
      tile.west_tile = &west_tile;
  }
}
