#ifndef DAY_15_HPP
#define DAY_15_HPP

#include "Solver.hpp"

namespace DAY15
{

const uint32_t MAX_LINE_SIZE     = 22860;
const uint32_t MAX_NUM_STRINGS   = 4000;
const uint32_t MAX_STRING_LENGTH = 32;
const uint32_t MAX_NUM_LENSES    = 256;
const uint32_t MAX_NUM_BOXES     = 256;

struct Lens
{
  char label[MAX_STRING_LENGTH];
  uint32_t focal_length;

  Lens() : focal_length(0) { memset(label, 0, sizeof(label)); }
};

struct Box
{
  uint32_t num_lenses;
  Lens lenses[MAX_NUM_LENSES];

  Box() : num_lenses(0) { memset(lenses, 0, sizeof(lenses)); }

  void RemoveLens(char* lens_label)
  {
    bool lens_found = false;
    for (uint32_t i = 0; i < num_lenses; i++)
    {
      if (!lens_found && strcmp(lenses[i].label, lens_label) == 0)
      {
        lens_found = true;
      }
      if (lens_found && i < num_lenses - 1)
      {
        Lens swap     = lenses[i];
        lenses[i]     = lenses[i + 1];
        lenses[i + 1] = swap;
      }
    }
    if (lens_found)
      num_lenses--;
  }

  void AddLens(char* lens_label, uint8_t focal_length)
  {
    bool lens_found = false;
    for (uint32_t i = 0; i < num_lenses && !lens_found; i++)
    {
      if (strcmp(lenses[i].label, lens_label) == 0)
      {
        lens_found             = true;
        lenses[i].focal_length = focal_length;
      }
    }
    if (!lens_found && num_lenses < MAX_NUM_LENSES)
    {
      strcpy(lenses[num_lenses].label, lens_label);
      lenses[num_lenses].focal_length = focal_length;
      num_lenses++;
    }
  }
};

class Day15 : public Solver
{
  public:
  Day15();
  ~Day15();
  void Initialize(RETURN_CODE_TYPE::Value& return_code);
  void Configure(const ConfigurationResource configuration_resource,
                 RETURN_CODE_TYPE::Value& return_code);
  void Solve(RETURN_CODE_TYPE::Value& return_code);
  void Finalize(RETURN_CODE_TYPE::Value& return_code);

  private:
  uint32_t m_num_strings;
  char m_strings[MAX_NUM_STRINGS][MAX_STRING_LENGTH];
  Box m_boxes[MAX_NUM_BOXES];
};

} // namespace DAY15

#endif // DAY_15_HPP