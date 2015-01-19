.PHONY: clean

all: main simple_plugin.so better_plugin.so

%.so: %.c
	gcc -shared -o $@ -fpic $<

main: main.c
	gcc -o $@ $< -ldl

clean:
	rm *.so main
