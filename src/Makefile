CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -Wpedantic
DEPS=../include/stack.h ../include/types.h
OBJ=$(addprefix build/,stack.o esil.o main.o)
OBJ_TEST=$(addprefix build_test/,stack.o esil.o test.o)

esil: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

tests: $(OBJ_TEST)
	$(CC) -o $@ $^ -g -DTEST $(CFLAGS)

build_test/%.o: %.c $(DEPS)
	$(CC) -c -o $@ -DTEST $< $(CFLAGS)

build/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm build/* build_test/* esil tests
