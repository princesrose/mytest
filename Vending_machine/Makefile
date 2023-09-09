SRCS=$(wildcard ./src/*.c)
CC:=gcc 
RF:=rm -rf

.PHONY:
all:
	$(CC) -c $(SRCS) -I ./include
	ar -cr ./src/libtest.a *.o
	$(CC) 自动贩卖机.c -o 1 -L ./src -ltest -I ./include
.PHONY:
clean:
	$(RF) *.o