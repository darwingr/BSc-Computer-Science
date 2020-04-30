include ../mpi.mk
include ../clean.mk

all: data-type-1-contiguous \
	data-type-2-vector \
	data-type-3-indexed \
	data-type-4-struct

.PHONY: dt1 dt2 dt3 dt4
# Check that it runs
dt1: data-type-1-contiguous
	$(call run-mpi-battery,4)

dt2: data-type-2-vector
	$(call run-mpi-battery,4)

dt3: data-type-3-indexed
	$(call run-mpi-battery,4)

dt4: data-type-4-struct
	$(call run-mpi-battery,4)

C_TARGETS := 
$(C_TARGETS): CC := cc
$(C_TARGETS): LDFLAGS :=
$(C_TARGETS): %.o : %.c

project_label:=Lab7
ordered_docs := Lab7-dt1.md data-type-1-contiguous.c \
				Lab7-dt2.md data-type-2-vector.c \
				Lab7-dt3.md data-type-3-indexed.c \
				Lab7-dt4.md data-type-4-struct.c

TITLE:=$(shell cat title.txt)
include ../publish.mk
