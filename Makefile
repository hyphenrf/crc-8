#
# Makefile

CC     ?= gcc
CFLAGS ?= $(shell "paste" "-sd " "compile_flags.txt")

test: test.c crc.o

crc.o: crc.c

run: test
	@./test

clean:
	-rm -rf test *.o release/

release:
	@mkdir -p release
	@find |sed 's:^./*::;1d;/^release$$/d' \
	      |zip -l@ release/release.zip
	@echo "------------------------"
	@echo "see: release/release.zip"

.PHONY: clean run release
# vim:ft=make
#
