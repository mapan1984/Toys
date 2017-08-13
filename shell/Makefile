CC = gcc

# -wall 打开所有警告
# -I .  在当前目录下寻找hello.c中包含的头文件
CFLAGS = -O2 -Wall -I .

# This flag includes the Pthreads library on a Linux box.
# Others systems will probably require something different.
LIB = -lpthread

all: hello shell

shell: shell.o base.o
	$(CC) $(CFLAGS) -o shell shell.o base.o $(LIB)

shell.o: shell.c base.h
	$(CC) $(CFLAGS) -c shell.c

base.o:
	$(CC) $(CFLAGS) -c base.c

hello: hello.c
	$(CC) $(CFLAGS) -o hello hello.c

clean:
	rm -f *.o hello shell *~
