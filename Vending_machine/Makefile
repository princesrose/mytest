SRCS=$(wildcard ./src/*.c)
CC:=gcc 
RF:=rm -rf

all:
	$(CC) -c $(SRCS) -I ./include
	ar -cr ./lib/libxjz.a *.o
	$(CC) -fPIC -shared $(SRCS) -Iinclude -o ./lib/libxjz.so
	$(CC) 自动贩卖机.c ./lib/libxjz.a -o 1 -Iinclude
# $(CC) 自动贩卖机.c -o 1 -Iinclude -Llib -lxjz
# -I（大写的i      Include）：告诉编译器在哪里找头文件
# -L（库Lib）：告诉编译器在哪里找库文件
# -l   (小写的L)：要链接哪个动态库，写库名（即add）
# .PHONY:clean的作用是当工作路径中有clean文件时，执行make clean会提示make: 'clean' is up to date.
# 因此要加.PHONY:忽略掉clean，不要让make认为clean是目标文件，并强制执行clean命令
.PHONY:clean
clean:
	$(RF) *.o