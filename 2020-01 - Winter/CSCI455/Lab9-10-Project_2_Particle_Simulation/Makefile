include ../mpi.mk
include ../clean.mk

all: partsim

physics.o : physics.c physics.h coordinate.h
random.o  : random.c random.h
partsim.o : partsim.c definitions.h physics.h coordinate.h

partsim : partsim.o physics.o random.o

.PHONY: run q2
run: partsim
	$(run-mpi)

q2: partsim
	$(call run-mpi-battery,1 2 4 8 16 32 64 96,)


C_TARGETS := 
$(C_TARGETS): CC := cc
$(C_TARGETS): LDFLAGS :=
$(C_TARGETS): %.o : %.c

project_label:=Lab9-10
ordered_docs := questions.md \
				partsim.c \
				physics.h physics.c \
				definitions.h coordinate.h \
				random.h random.c \
				Makefile
document_assets :=
TITLE:=$(shell cat title.txt)
# CSCI 455: Lab #9 & #10 — Gas Laws and Brownian Motion
#TITLE:=Project 2 — Particle Simulation
#TITLE:=Lab \#9 & \#10 — Gas Laws and Brownian Motion
#TITLE:=Lab \#9 & \#10 — Particle Simulation

include ../publish.mk
