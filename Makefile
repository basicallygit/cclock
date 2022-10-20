.PHONY: main
main: main.c
	cc -o cclock main.c

.PHONY: install
install:
	mv cclock /usr/bin/cclock
