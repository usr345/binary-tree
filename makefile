ifeq ($(TARGET),linux)
        CC = gcc
else
        CC = CL.exe
endif

linear_search: linear_search.c
	$(CC) -Wall -I ../algorithms -o linear_search linear_search.c ../algorithms/binary_tree.c ../algorithms/stack.c

binary_test: binary_test.c
	$(CC) -Wall -D LINUX -o binary_test binary_test.c binary_tree.c stack.c
