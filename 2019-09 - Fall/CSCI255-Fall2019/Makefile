SUBDIRS := $(wildcard Lab*/)
HANDINS := ''

# https://stackoverflow.com/questions/17834582/run-make-in-each-subdirectory#17845120


all:
	echo $(SUBDIRS)

handins_dir="CSCI 255-Handins"

# will not expect 
#publish: $(SUBDIRS)
publish:
	mv Lab*/Lab*-HANDIN.pdf $(handins_dir)

$(SUBDIRS):
	$(MAKE) -C $@ vars

.PHONY: publish $(SUBDIRS)
