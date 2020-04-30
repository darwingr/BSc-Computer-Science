#!/usr/bin/env bash
#
#
# ssh -t aws-mpi "sudo cluster-provision.sh"

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


# 1. PROVISIONING (hardware & libraries)
#   Code to be run from the AWS Console when it sets up a new VM.
#
#   AWS Cluster:
#   - EC2 virtual server
#   - On-Demand pricing (billed per second, 60 second minimum)
#   - Region: Canada (central) ca-central-1
#   - template: csci455-lab-cluster
#   - AMI (image): Ubuntu Server 18.04 LTS, hardware virtual machine (HVM)
#   - Compute Optimized instance
#   - c5.24xlarge
#     - 96 vCPU cores (48 cores with hyperthreading @ 3.6 GHz)
#     - $4.464 USD per Hour (July 2nd, 2020)
#     - Intel Xeon Scalable Processors (Cascade Lake)
#     - EC2 Instance Store: temporary store
#     - EBS: some hybrid storage device
#     - C5d include local NVMe-based SSD, physically attached block-level store
#   - c5.large (for testing)
#     - 2 vCPU (4GiB memory)
#     - $0.093 USD / hr
#     - $0.25 CAD for 2 hours
#     - default storage: 8GiB
#   - Add inbound security rule for ssh (not default)

# 2. DEPLOYMENT

# 3. EXECUTION

# 4. SCREENSHOT & DOCUMENT RETREIVAL



# boot system
# updated packages
sudo apt update

# install make
# install gcc/g++ compiler, c/c++ libraries
sudo apt -y install build-essential

# Extras
sudo apt -y install htop

# hwloc, an open-mpi dependency for processor/memory affinity and NUMA.
#   otherwise ompi >= V4 will just use bundled hwloc/libevent.
sudo apt -y install hwloc

# OpenMPI v3
# install open-mpi dependency
#sudo apt-get -y install libblacs-mpi-dev


# OpenMPI v4
wget https://download.open-mpi.org/release/open-mpi/v4.0/openmpi-4.0.4.tar.gz
gunzip -c openmpi-4.0.4.tar.gz | tar xf -
cd openmpi-4.0.4
./configure --prefix=/usr/local
make -j $(nproc) all
sudo make install

# Already handled under /etc/ld.so.conf.d/libc.conf,
#   put there by installing gcc with build-essential.
#echo 'export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH' >> $HOME/.bashrc
#export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
sudo ldconfig

cd ..
#sudo rm -rf openmpi-4.0.4
rm openmpi-4.0.4.tar.gz

