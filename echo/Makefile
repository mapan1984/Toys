CC = gcc

# -wall 打开所有警告
# -I .  在当前目录下寻找echoserveri.c中包含的头文件
CFLAGS = -O2 -Wall -I .

# This flag includes the Pthreads library on a Linux box.
# Others systems will probably require something different.
LIB = -lpthread

all: echoclient echoserver

echoclient: echoclient.c csapp.o
	$(CC) $(CFLAGS) -o echoclient echoclient.c csapp.o $(LIB)

echoserver: echoserver.c csapp.o
	$(CC) $(CFLAGS) -o echoserver echoserver.c csapp.o $(LIB)

csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) -c csapp.c

clean:
	rm -f *.o echoserver echoclient *~
