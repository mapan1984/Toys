CC = gcc

# -wall 打开所有警告
# -I .  在当前目录下寻找hostinfo.c中包含的头文件
CFLAGS = -O2 -Wall -I .

# This flag includes the Pthreads library on a Linux box.
# Others systems will probably require something different.
LIB = -lpthread

hostinfo: hostinfo.o csapp.o
	$(CC) $(CFLAGS) -o hostinfo hostinfo.o csapp.o $(LIB)

hostinfo.o: hostinfo.c csapp.h
	$(CC) $(CFLAGS) -c hostinfo.c
csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) -c csapp.c

clean:
	rm -f *.o hostinfo *~

install:
	mv hostinfo /bin
