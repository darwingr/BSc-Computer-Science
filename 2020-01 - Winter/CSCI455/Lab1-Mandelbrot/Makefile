include ../mpi.mk
include ../clean.mk

.PHONY: all
all:


.PHONY: sample_mandelbrot
# Run with processors set to 2, 4, 8, 12, 16, 24, and list the results in table.
sample_mandelbrot: mandelbrot_parallel
	@echo "Platform: $(UNAME) ($(procs) cpu cores recognized)"
	for nodeprocs in 2 4 8 12 16 24 ; do \
		echo "\nMPIRUN $< with $$nodeprocs node processes:" ; \
		$(MPIRUN) -np $$nodeprocs  ./$< $(prepath)/image-$$nodeprocs.ppm ; \
	done

.PHONY: run1
# Compile and Run
#image.ppm: mandelbrot_parallel
run1: mandelbrot_parallel
	$(call run-mpi,image.ppm)


.PHONY: run2
run2: hello_world
	$(run-mpi)

.PHONY: sample_hello_world
sample_hello_world: hello_world
	@echo "Platform: $(UNAME) ($(procs) cpu cores recognized)"
	for nodeprocs in 4 8 16 ; do \
		echo "\nMPIRUN $< with $$nodeprocs node processes:" ; \
		$(MPIRUN) -np $$nodeprocs ./$< ; \
	done

vpath %.png ./assets
vpath %.jpg ./assets

project_label:=Lab1
ordered_docs := question1.md \
				mandelbrot_parallel.cpp \
				question2.md \
				hello_world.cpp
document_assets :=  image.jpg  \
					run1-cluster.png \
					sample_mandelbrot-cluster.png \
					sample_hello_world-cluster.png
TITLE:=$(shell cat title.txt)
include ../publish.mk
