test: allocator.o test.o
	gcc -g allocator.o test.o -o test
test.o: test.c
	gcc -g -c test.c
allocator.o: allocator.c
	gcc -g -c allocator.c
clean:
	rm -f allocator.o test.o test
