include ../mpi.mk
include ../clean.mk

.PHONY: run1 run2
run1: parpi
	$(run-mpi)
run2: parpi
	$(call run-mpi,2)


parpi.log: parpi
	$(run-mpi) | tee $@

.PHONY: sample_parpi
sample_parpi: parpi
	$(call run-mpi-battery,5 10 20 40 60)

.PHONY: sample_parpi2
sample_parpi2: parpi
	$(call run-mpi-battery,5 10 20 40 60,2)


.PHONY: sample_parpi_extended sample_parpi2_extended
# Expect algorithm to peak around 4 cores,
#   as per graph on page 205, Intro to Parallel Computing (2018)
sample_parpi_extended: parpi
	$(call run-mpi-battery,1 2 3 4 5 10 20 40 60 80 96)
sample_parpi2_extended: parpi
	$(call run-mpi-battery,1 2 3 4 5 10 20 40 60 80 96,2)


C_TARGETS := 
$(C_TARGETS): CC := cc
$(C_TARGETS): LDFLAGS :=
$(C_TARGETS): % : %.c

project_label:=Lab3
ordered_docs := questions.md \
				parpi.c

vpath %.png ./assets
document_assets:= \
	make-sample_parpi_extended-cluster.png \
	make-run1_run2-cluster.png \
	make-sample_parpi2_extended-cluster.png

TITLE:=$(shell cat title.txt)
include ../publish.mk
