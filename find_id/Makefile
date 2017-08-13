objects = myid.o add_item.o find_item.o del_item.o base.o

myid: $(objects)
	gcc -o myid $(objects)

myid.o: myid.c myid.h
	gcc -c myid.c
add_item.o: add_item.c myid.h
	gcc -c add_item.c
find_item.o: find_item.c myid.h
	gcc -c find_item.c
del_item.o: del_item.c myid.h
	gcc -c del_item.c
base.o: base.c myid.h
	gcc -c base.c

.PHONY: clean
clean:
	-rm myid $(objects)
