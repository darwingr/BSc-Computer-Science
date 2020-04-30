#!/usr/bin/env bash
#
# ./cluster-machine.sh
# ./cluster-machine.sh small
# ./cluster-machine.sh big
#

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

aws_template_id="lt-0c708a8b277bacfc1"
aws_profile="darwin-mpi"
# test=c5.large
# prod=c5.24xlarge
aws ec2 describe-instances --profile darwin-mpi
opt=$1
case $opt in
  sm*)
    aws ec2 run-instances \
      --profile $aws_profile \
      --launch-template LaunchTemplateId=$aws_template_id \
      --instance-type c5.large
      ;;
  *)
    ;;
esac
