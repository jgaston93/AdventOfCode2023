#include <stdio.h>

#include <cstring>

// array of digit strings for comparison
char digit_strings[][8] = {"one", "two",   "three", "four", "five",
                           "six", "seven", "eight", "nine"};

int main(int argc, char** argv) {
  if (argc < 3) {
    return 1;
  }

  bool check_for_strings = false;
  if (strcmp(argv[1], "part1") == 0) {
    check_for_strings = false;
  } else if (strcmp(argv[1], "part2") == 0) {
    check_for_strings = true;
  } else {
    return 1;
  }

  FILE* fp = 0;
  fp = fopen(argv[2], "r");

  char line[256];

  unsigned int calibration_values_sum = 0;

  // iterate over each line in the file
  while (fgets(line, sizeof(line), fp) != 0) {
    unsigned int first = 0, last = 0;
    char current_char = line[0];
    unsigned int line_index = 1;
    bool first_digit_found = false;

    // iterate over each character in line until
    // newline or null terminator found
    while (current_char != '\n' && current_char != '\0') {
      unsigned int digit = 0;
      bool digit_found = false;
      // check if character is a number
      if ('0' <= current_char && current_char <= '9') {
        digit = current_char - '0';
        digit_found = true;
      }
      // check if number is spelled out
      else if (check_for_strings) {
        // get length of remaining line
        unsigned int line_length = strlen(&(line[line_index - 1]));

        // iterate over digit strings
        for (unsigned int i = 0; i < 9 && !digit_found; i++) {
          // get length of digit string
          unsigned int digit_string_length =
              strlen((const char*)&digit_strings[i]);

          // ensure that remaining line length is
          // at least as long as digit string length
          if (line_length >= digit_string_length) {
            // check if strings are equal
            if (strncmp((const char*)&digit_strings[i], &(line[line_index - 1]),
                        digit_string_length) == 0) {
              digit = i + 1;
              digit_found = true;
            }
          }
        }
      }

      if (digit_found) {
        // Set last to current found digit
        last = digit;
        // If first digit is found set the first character
        if (!first_digit_found) {
          first = digit;
          first_digit_found = true;
        }
      }

      current_char = line[line_index++];
    }
    calibration_values_sum += (first * 10) + last;
  }
  fclose(fp);

  printf("Sum of all calibration values is %lu\n", calibration_values_sum);
  return 0;
}