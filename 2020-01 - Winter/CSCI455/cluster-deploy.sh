#!/usr/bin/env bash
#
#
# just run it

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

scp cluster-provision.sh aws-mpi:~/


rsync -avze 'ssh'       \
  --include="*.mk"      \
  --include="Makefile"  \
  --include="Lab*/***"  \
  --exclude="*"         \
  . aws-mpi:~/csci455/

