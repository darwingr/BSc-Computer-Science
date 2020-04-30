include ../mpi.mk
include ../clean.mk

mpi_latency: slr.o

.PHONY: run1
run1: mpi_latency
	$(run-mpi)


.PHONY: test_mpi_latency
test_mpi_latency: mpi_latency
	# TODO 2: Run first code (mpi_latency.c) on 2 processors with N (size) as
	#         10, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, respectively,
	#         to see the send/recv timing costs.
	$(call run-mpi-battery, 5 10 20 40 60)

.PHONY: test_parpi_extended
test_parpi_extended: parpi
	# TODO 3: Run the second code on 2, 4, 8, and 16 processors with
	#         (num_elements, num_trials) as (100, 100) and (200, 100).
	$(call run-mpi-battery, 1 2 3 4 5 10 20 40 60 80 100)


slr.o : slr.h
C_TARGETS := slr.o
$(C_TARGETS): CC := cc
$(C_TARGETS): LDFLAGS :=
$(C_TARGETS): %.o : %.c

project_label:=Lab4
ordered_docs := question1.md \
				mpi_latency.c              slr.h slr.c \
				question2.md \
				compare_bcast.c   hiding_latency.c

TITLE:=$(shell cat title.txt)
include ../publish.mk
