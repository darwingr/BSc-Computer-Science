.PHONY: all   # decoy
all:

CC  := mpicc
CFLAGS := -std=c99 -Wall -Wextra \
		  -g -D_GLIBCXX_DEBUG -O0
CXX := mpicxx
#	-stdlib=libc++    a clang flag
CXXFLAGS := -std=c++14 \
			-Wpedantic -Wall -Wno-missing-braces -Wextra \
			-g -D_GLIBCXX_DEBUG -O0
# Don't clobber the LDFLAGS set by mpicc!
#   These should be set in LDLIBS anyways, a makefile standard.
#LDFLAGS := -lmpi -lm
# Must include math library name on linux
LDLIBS += -lm
# Accept Intel Hyperthreads as Cores
MPIRUN = mpirun --use-hwthread-cpus


# Determine Node Processes from cores on system
#   MPI would determine this itself though
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	procs := $(shell sysctl -n hw.physicalcpu_max)
	# MacOS issue:
	#   https://github.com/open-mpi/ompi/issues/5798#issuecomment-426271555
	MPIRUN = PMIX_MCA_gds=hash \
			mpirun \
			--host localhost \
			--mca btl_vader_backing_directory /tmp \
			--mca btl ^tcp \
			--oversubscribe #\
			# Setting localhost does not help, is not exclusive
			#--hosts localhost #\ firewall warnings on MacOS #\
			#--report-pid
	prepath = /tmp
else ifeq ($(UNAME), Linux)
	procs := $(shell nproc)
	prepath = .
else
	procs := 1
    $(info can't determine OS or cores count, setting to 1.)
	prepath = .
endif


# No '=' on canned recipe for compatibility with old GNUMake

# Usage:
#   $(run-mpi)
#   $(run-mpi) my_args here
#   $(call run-mpi,my_args here)
define run-mpi
    @echo "Platform: $(UNAME) ($(procs) cpu cores recognized)"
    $(MPIRUN) -np $(procs) ./$< $1
endef

# Usage:
#   $(call run-mpi-battery,1,)
#   $(call run-mpi-battery,5 10 20 40 60,command args here)
define run-mpi-battery
    @echo "Platform: $(UNAME) ($(procs) cpu cores recognized)"
    @for nodeprocs in $1 ; do \
        echo "MPIRUN $< with $$nodeprocs node processes:" ; \
        $(MPIRUN) -np $$nodeprocs  ./$< $2 ; \
    done
endef

# End of Standard MPI Makefile #################################################
