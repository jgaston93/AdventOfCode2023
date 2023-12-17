#include <cstdio>
#include <cstring>

#include "Day16.hpp"

using namespace DAY16;

Day16::Day16() : m_grid_size(0), m_num_beams(0), m_beam_id(0) {}

Day16::~Day16()
{
  RETURN_CODE_TYPE::Value return_code = RETURN_CODE_TYPE::NO_ERROR;
  Finalize(return_code);
}

void Day16::Initialize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day16::Configure(const ConfigurationResource configuration_resource,
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

    uint32_t row_counter = 0;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
      if (m_grid_size == 0)
        m_grid_size = strlen(line) - 1;

      if (line[m_grid_size] == '\n')
        line[m_grid_size] = '\0';

      for (uint32_t i = 0; i < m_grid_size; i++)
      {
        switch (line[i])
        {
        case '|':
          m_tiles[row_counter][i].type = VerticalSplitter;
          break;
        case '-':
          m_tiles[row_counter][i].type = HorizontalSplitter;
          break;
        case '/':
          m_tiles[row_counter][i].type = RightMirror;
          break;
        case '\\':
          m_tiles[row_counter][i].type = LeftMirror;
          break;
        default:
          m_tiles[row_counter][i].type = Empty;
          break;
        }
      }
      row_counter++;
    }

    fclose(fp);
  }
}

void Day16::Solve(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;

  m_beams[0].beam_id = m_beam_id++;
  m_beams[0].vel_x   = 1;
  m_num_beams        = 1;

  Interact(m_beams[0], m_tiles[m_beams[0].y][m_beams[0].x]);

  bool running          = true;
  uint32_t step_counter = 0;

  while (running)
  {
    uint32_t current_num_beams = m_num_beams;
    for (uint32_t i = 0; i < current_num_beams; i++)
    {
      Beam& beam = m_beams[i];

      beam.x += beam.vel_x;
      beam.y += beam.vel_y;

      if (beam.x < 0)
      {
        beam.x     = 0;
        beam.vel_x = 0;
      }
      else if (beam.x >= m_grid_size)
      {
        beam.x     = m_grid_size - 1;
        beam.vel_x = 0;
      }

      if (beam.y < 0)
      {
        beam.y     = 0;
        beam.vel_y = 0;
      }
      else if (beam.y >= m_grid_size)
      {
        beam.y     = m_grid_size - 1;
        beam.vel_y = 0;
      }

      Interact(beam, m_tiles[beam.y][beam.x]);
    }

    for (uint32_t i = 0; i < m_num_beams; i++)
    {
      if (m_beams[i].vel_x == 0 && m_beams[i].vel_y == 0)
      {
        for (uint32_t j = i; j < m_num_beams - 1; j++)
        {
          Beam swap      = m_beams[j];
          m_beams[j]     = m_beams[j + 1];
          m_beams[j + 1] = swap;
        }
        m_num_beams--;
      }
    }
    if (step_counter++ > 2000)
      running = false;
  }

  uint32_t energy_sum = 0;
  for (uint32_t i = 0; i < m_grid_size; i++)
  {
    for (uint32_t j = 0; j < m_grid_size; j++)
    {
      if (m_tiles[i][j].energy_level > 0)
      {
        energy_sum++;
        printf("#");
      }
      else
        printf(".");
    }
    printf("\n");
  }
  printf("\n");
  printf("Part 1 solution: %lu\n", energy_sum);
}

void Day16::Finalize(RETURN_CODE_TYPE::Value& return_code)
{
  return_code = RETURN_CODE_TYPE::NO_ERROR;
}

void Day16::Interact(Beam& beam, Tile& tile)
{
  tile.energy_level++;

  if (tile.type == LeftMirror)
  {
    if (beam.vel_x > 0)
    {
      beam.vel_x = 0;
      beam.vel_y = 1;
    }
    else if (beam.vel_x < 0)
    {
      beam.vel_x = 0;
      beam.vel_y = -1;
    }
    else if (beam.vel_y > 0)
    {
      beam.vel_y = 0;
      beam.vel_x = 1;
    }
    else if (beam.vel_y < 0)
    {
      beam.vel_y = 0;
      beam.vel_x = -1;
    }
  }

  else if (tile.type == RightMirror)
  {
    if (beam.vel_x > 0)
    {
      beam.vel_x = 0;
      beam.vel_y = -1;
    }
    else if (beam.vel_x < 0)
    {
      beam.vel_x = 0;
      beam.vel_y = 1;
    }
    else if (beam.vel_y > 0)
    {
      beam.vel_y = 0;
      beam.vel_x = -1;
    }
    else if (beam.vel_y < 0)
    {
      beam.vel_y = 0;
      beam.vel_x = 1;
    }
  }
  else if (tile.type == VerticalSplitter)
  {
    bool beam_found = false;
    for (uint32_t i = 0; i < tile.num_visited_beams && !beam_found; i++)
    {
      if (beam.beam_id == tile.visited_beams[i])
        beam_found = true;
    }

    if (beam_found && beam.vel_x != 0)
    {
      beam.vel_x = 0;
      beam.vel_y = 0;
    }
    else
    {
      if (beam.vel_x > 0)
      {
        beam.vel_x = 0;
        beam.vel_y = -1;

        if (tile.num_visited_beams < MAX_NUM_BEAMS)
          tile.visited_beams[tile.num_visited_beams++] = beam.beam_id;
        else
          printf("Too many visited beams\n");

        if (m_num_beams < MAX_NUM_BEAMS)
        {
          m_beams[m_num_beams].beam_id = m_beam_id++;
          m_beams[m_num_beams].x       = beam.x;
          m_beams[m_num_beams].y       = beam.y;
          m_beams[m_num_beams].vel_x   = 0;
          m_beams[m_num_beams].vel_y   = 1;

          if (tile.num_visited_beams < MAX_NUM_BEAMS)
            tile.visited_beams[tile.num_visited_beams++] =
              m_beams[m_num_beams].beam_id;
          else
            printf("Too many visited beams\n");

          m_num_beams++;
        }
        else
        {
          // printf("Warning too many beams created\n");
        }
      }
      else if (beam.vel_x < 0)
      {
        beam.vel_x = 0;
        beam.vel_y = 1;

        if (tile.num_visited_beams < MAX_NUM_BEAMS)
          tile.visited_beams[tile.num_visited_beams++] = beam.beam_id;
        else
          printf("Too many visited beams\n");

        if (m_num_beams < MAX_NUM_BEAMS)
        {
          m_beams[m_num_beams].beam_id = m_beam_id++;
          m_beams[m_num_beams].x       = beam.x;
          m_beams[m_num_beams].y       = beam.y;
          m_beams[m_num_beams].vel_x   = 0;
          m_beams[m_num_beams].vel_y   = -1;

          if (tile.num_visited_beams < MAX_NUM_BEAMS)
            tile.visited_beams[tile.num_visited_beams++] =
              m_beams[m_num_beams].beam_id;
          else
            printf("Too many visited beams\n");

          m_num_beams++;
        }
        else
        {
          // printf("Warning too many beams created\n");
        }
      }
    }
  }
  else if (tile.type == HorizontalSplitter)
  {
    bool beam_found = false;
    for (uint32_t i = 0; i < tile.num_visited_beams && !beam_found; i++)
    {
      if (beam.beam_id == tile.visited_beams[i])
        beam_found = true;
    }

    if (beam_found && beam.vel_y != 0)
    {
      beam.vel_x = 0;
      beam.vel_y = 0;
    }
    else
    {
      if (beam.vel_y > 0)
      {
        beam.vel_y = 0;
        beam.vel_x = -1;

        if (tile.num_visited_beams < MAX_NUM_BEAMS)
          tile.visited_beams[tile.num_visited_beams++] = beam.beam_id;
        else
          printf("Too many visited beams\n");

        if (m_num_beams < MAX_NUM_BEAMS)
        {
          m_beams[m_num_beams].beam_id = m_beam_id++;
          m_beams[m_num_beams].x       = beam.x;
          m_beams[m_num_beams].y       = beam.y;
          m_beams[m_num_beams].vel_y   = 0;
          m_beams[m_num_beams].vel_x   = 1;

          if (tile.num_visited_beams < MAX_NUM_BEAMS)
            tile.visited_beams[tile.num_visited_beams++] =
              m_beams[m_num_beams].beam_id;
          else
            printf("Too many visited beams\n");

          m_num_beams++;
        }
        else
        {
          // printf("Warning too many beams created\n");
        }
      }
      else if (beam.vel_y < 0)
      {
        beam.vel_y = 0;
        beam.vel_x = 1;

        if (tile.num_visited_beams < MAX_NUM_BEAMS)
          tile.visited_beams[tile.num_visited_beams++] = beam.beam_id;
        else
          printf("Too many visited beams\n");

        if (m_num_beams < MAX_NUM_BEAMS)
        {
          m_beams[m_num_beams].beam_id = m_beam_id++;
          m_beams[m_num_beams].x       = beam.x;
          m_beams[m_num_beams].y       = beam.y;
          m_beams[m_num_beams].vel_y   = 0;
          m_beams[m_num_beams].vel_x   = -1;

          if (tile.num_visited_beams < MAX_NUM_BEAMS)
            tile.visited_beams[tile.num_visited_beams++] =
              m_beams[m_num_beams].beam_id;
          else
            printf("Too many visited beams\n");

          m_num_beams++;
        }
        else
        {
          // printf("Warning too many beams created\n");
        }
      }
    }
  }
}