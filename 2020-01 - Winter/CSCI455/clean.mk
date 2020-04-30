.PHONY: all   # decoy
all:

.PHONY: clean
clean: clean-basics

.PHONY: clean-basics
clean-basics:
	# Generally useful defaults
	rm -f \
        *.o \
        a.out main.out \
        *.dep *.d \
        *.gch
	rm -rf *.dSYM
	# Extensionless executable files...risky?
	find . -type f -perm -u=x -not -iname "*.*" -delete
	# Project helper files
	rm -f \
        make-*-deps.png \
        compile_commands.json \
        tags

