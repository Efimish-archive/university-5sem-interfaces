#!/usr/bin/env bash

# Check if filename is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <file.cpp> [<c++ options>]"
  exit 1
fi

# Compile the C++ file
g++ "$1" -o "${1%.cpp}.out" -I/opt/homebrew/include -L/opt/homebrew/lib -lboost_program_options
if [ $? -ne 0 ]; then
  echo "Compilation failed."
  exit 1
fi

# Run the executable with arguments
./"${1%.cpp}.out" "${@:2}"

# Cleanup
rm -f "${1%.cpp}.out"
