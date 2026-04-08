CC = gcc

.PHONY: all clean run install uninstall

all: main.c
	mkdir -p build
	$(CC) main.c -o build/myfetch

clean:
	rm -rf build

run: build/myfetch
	build/myfetch

install: build/myfetch
	install -m 755 build/myfetch /usr/bin/myfetch

uninstall:
	rm -f /usr/bin/myfetch
