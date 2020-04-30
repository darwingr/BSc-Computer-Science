.PHONY: all
all:


LABSUBDIRS := $(wildcard ./Lab*)

.PHONY: $(LABSUBDIRS)
clean: $(LABSUBDIRS)

$(LABSUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

# On submission of appeal, Monday Jun 17th
handins-v2:
	touch -am -t 202005142049.33 CSCI455-Handins/Lab*-HANDIN.pdf
