#ifndef __MYID_H__
#define __MYID_H__

#include <stdio.h>  // perror()
#include <errno.h>  // errno
#include <stdlib.h>  // exit()
#include <string.h>

#define IDLIST "idlist"
#define INIT_LEN 1024
#define IC 100

typedef struct{
    char *base;
    int size;
}allItem;

extern void getitemhead(int item_len, char const *item, char *itemhead);
extern void getitemtail(int item_len, char const *item, char *itemtail);
extern void initAllItem(allItem *allitem);
extern void saveItem(FILE *file, allItem *allitem);
extern void addItem(char const *item, char const *name, char const *id, char const *password);
extern void findItem(char const *item);
extern void delItem(char const *item);

/* base fun */
extern FILE *Fopen(char const *filename, char const *mode);
extern void Fclose(FILE *file);
extern char *Strstr(char const *s1, char const *s2);
extern void *Malloc(size_t size);
extern void *Realloc(void *ptr, size_t new_size);

#endif
