#!/usr/bin/env bash
#
# Fetch the produced files from server/cluster,
#   needed for building LaTeX document handins.


# Fail fast
#set -o noclobber  # Avoid overlay files (echo "hi" > foo)
set -o errexit    # Used to exit upon error, avoiding cascading errors
set -o pipefail   # Unveils hidden failures
set -o nounset    # Exposes unset variables

# Debug
#set -o noexec     # Read commands in script, don't execute them (syntax check).
#set -o noglob     # Disable file name expansion (globbing).
set -o verbose    # Prints shell input lines as they are read.
#set -o xtrace     # Print command traces before executing command.
 
Lab1:
  run1:
    - fetch image.ppm
    - take screenshot
  sample_mandelbrot:
    - take screenshot (optional)
    - save output for table

  run2:
    - nothing
  sample_hello_world:
    - take screenshot

Lab2:
  parsum.log: same as run
    - save output from parsum.log
    - take screenshot (first and last)

Lab3:
  run1 run2:
    - take screenshot

  sample_parpi_extended:
    - take screenshot

  sample_parpi2_extended:
    - take screenshot

Lab4:
  run1:
  - take screenshots (3)
  test_mpi_latency:
    - save output (14 pages)

Lab5:
  - do nothing, only required 4 cpu cluster

Lab6: ? new screenshots (to supplement old ones)
  p1-2
  p2-2
  p3

