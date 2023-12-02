# Advent of Code 2023

Hello! These are my solutions for Advent of Code 2023.


## Build

I use a combination of CMake and MinGW for building the source code in this repo.

Here are the build instructions I use:
```
cmake -Bbuild -S./ -G "MinGW Makefiles"
cmake --build build/
```

## Execute

Configuration files are used to determine which solution and input file to use when executing the program.

After running the build steps above these commands can be used to run the solutions.
```
./build/aoc_driver.exe -c config/Day01/Configuration_File.json
```
