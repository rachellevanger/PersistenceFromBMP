#!/bin/bash


# Configure directory for persistence diagram output
mkdir -p PD/DownUp/Diagrams
mkdir -p PD/UpDown/Diagrams

# Run BMPPersistence app on the 7 test files
../BMPPersistence 1 7 ./ bmps/test%d.bmp 1 1 0


# Compare test output to expected output
# TO DO: Write this test.

