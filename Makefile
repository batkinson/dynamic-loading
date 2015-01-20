.PHONY: clean

CC=g++
CFLAGS=-std=c++0x -Wall -Wextra

all: main simple_plugin.so better_plugin.so

%.so: %.cpp
	$(CC) $(CFLAGS) -shared -o $@ -fpic $<

main: main.cpp
	$(CC) $(CFLAGS) -o $@ $< -ldl

clean:
	rm *.so main
