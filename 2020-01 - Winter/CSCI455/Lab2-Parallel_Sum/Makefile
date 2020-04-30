include ../mpi.mk
include ../clean.mk

all: parsum

.PHONY: run
run: parsum
	$(call run-mpi,given/rand_data.txt)

%: %.c trace.h

# suggested:
#$(mpirun) -p all -np 10 ./$< | tee $@
# But '-p all' is not a listed option in open-mpi or mpich.
parsum.log: parsum
	$(call run-mpi,given/rand_data.txt | tee $@)




C_TARGETS := seqsum test_looping
$(C_TARGETS): CC := cc
$(C_TARGETS): LDFLAGS :=
$(C_TARGETS): % : %.c

project_label:=Lab2
ordered_docs := questions.md \
				console.tex \
				parsum.c \
				seqsum.c \
				trace.h

vpath %.png ./assets
document_assets:=   assets/parsum-cluster.log \
					make-parsum-cluster-1.png \
					make-parsum-cluster-2.png

TITLE:=$(shell cat title.txt)
include ../publish.mk
