#!/bin/bash
CLIENT_DIR=/home/mohan/.abc
all:rename
rename:xlat.c cleanup.sh
	gcc -ggdb xlat.c -o rename
.PHONY:clean
clean:
	@rm -fv *~ rename
.PHONY: rebuild
rebuild:
	make clean all
release:
	@cp -fv cleanup.sh $(CLIENT_DIR)