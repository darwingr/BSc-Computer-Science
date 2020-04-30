include ../mpi.mk
include ../clean.mk

vpath %.h      ./src
vpath %.c      ./src

clean: clean-ppm-images

all: transform-serial transform-parall test_filter

ppm.o :              ppm.c ppm.h
filter_ppm.o :       filter_ppm.c filter_ppm.h ppm.h

transform-serial.o : transform-serial.c ppm.h filter_ppm.h
transform-serial   : transform-serial.o ppm.o filter_ppm.o

transform-parall.o : transform-parall.c ppm.h filter_ppm.h
transform-parall   : transform-parall.o ppm.o filter_ppm.o

test_filter.o      : test_filter.c ppm.h filter_ppm.h
test_filter        : test_filter.o ppm.o filter_ppm.o

.PHONY:
test-filter: test_filter
	./$<

.PHONY: test-serial
test-serial: transform-serial
	./$<

.PHONY: test-parall
test-parall: transform-parall
	$(run-mpi)

.PHONY: test-parall-all
test-parall-all: transform-parall
	$(run-mpi) im1.ppm
	$(run-mpi) im2.ppm
	$(run-mpi) im3.ppm

# Run 4 times, drop the first for disk caching outliers
.PHONY: perf-q1
perf-q1: transform-parall transform-serial
	time ./transform-serial im1.ppm
	time $(MPIRUN) -np 1 ./transform-parall im1.ppm
	@echo -- Reject First, Keep Below --------------------------------
	time ./transform-serial im1.ppm
	time $(MPIRUN) -np 1 ./transform-parall im1.ppm
	time ./transform-serial im1.ppm
	time $(MPIRUN) -np 1 ./transform-parall im1.ppm
	time ./transform-serial im1.ppm
	time $(MPIRUN) -np 1 ./transform-parall im1.ppm

.PHONY: perf-q3
perf-q3: transform-parall
	time $(MPIRUN) -np 1 ./transform-parall im1.ppm
	@echo -- Reject First, Keep Below --------------------------------
	time $(MPIRUN) -np 1 ./transform-parall im1.ppm
	time $(MPIRUN) -np 2 ./transform-parall im1.ppm
	time $(MPIRUN) -np 4 ./transform-parall im1.ppm


# invoked by :clean
.PHONY: clean-ppm-images
clean-ppm-images:
	rm im?-*.ppm im?-*.pgm

# Merge all 3 to a single before and after image
#   requires ImageMagick
assets/%-merged.png : %.ppm %-parall-fuzzy.ppm %-parall-threshold.pgm
	magick montage -geometry 100% $^ $@

# old ImageMagick command
#	convert $^ +append $@
# from netpbm-package
#	pnmcat -lr <(pngtopnm 1.png) <(pngtopnm 2.png) | pnmtopng > all.png

project_label:=Lab5-6
ordered_docs := questions.md \
                src/transform-parall.c \
                src/filter_ppm.h   src/filter_ppm.c \
                src/ppm.h          src/ppm.c \
                src/transform-serial.c \
                Makefile

vpath %.png ./assets
document_assets:= im1-merged.png \
                  im2-merged.png \
                  im3-merged.png \
                  Screenshot-serial.png \
                  Screenshot-parall-all.png

TITLE:=$(shell cat title.txt)
include ../publish.mk
