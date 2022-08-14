build: image_filters.c image_filters.h main.c
	gcc -c image_filters.c
	gcc -c main.c
	gcc image_filters.o main.o -o my_filter

.PHONY: clean
clean:
	rm image_filters.o main.o my_filter