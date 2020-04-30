include ../mpi.mk
include ../clean.mk

all: group-incl            group-split \
     mpi-cart-1D-get-nbrs  mpi-cart-2D-get-nbrs \
     cannon

.PHONY: p1-1 p1-2
p1-1 : group-split
	$(run-mpi)
p1-2 : group-incl
	$(call run-mpi-battery,8)


.PHONY: p2-1 p2-2
p2-1 : mpi-cart-1D-get-nbrs
	$(run-mpi)
p2-2 : mpi-cart-2D-get-nbrs
	$(call run-mpi-battery,16)

.PHONY: p3 p3-suraj
p3: cannon
	$(call run-mpi-battery,16)
p3-suraj: cannon-suraj
	$(call run-mpi-battery,16)

C_TARGETS :=
$(C_TARGETS): CC := cc
$(C_TARGETS): LDFLAGS :=
$(C_TARGETS): %.o : %.c

project_label:=Lab8
ordered_docs := question1.md        group-split.c \
					question1-2.md  group-incl.c \
				question2.md        mpi-cart-1D-get-nbrs.c \
					question2-2.md  mpi-cart-2D-get-nbrs.c \
				question3.md cannon.c

vpath %.png ./assets
document_assets:= make-p1-1-split-local.png    make-p1-2-incl-cluster.png  \
				  make-p2-1-1D-local.png       make-p2-2-2D-cluster.png \
				  make-p3-cannon-cluster.png

#TITLE:=$(shell cat title.txt)
TITLE:=Lab \#8 — Advanced MPI: Group/Communicator Management and Virtual Topologies
include ../publish.mk
