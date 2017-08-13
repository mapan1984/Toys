#include "myid.h"

FILE *Fopen(char const *filename, char const *mode)
{
    FILE *idlist = fopen(filename, mode);
    if (idlist == NULL)
    {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    else
    {
        return idlist;
    }
}

void Fclose(FILE *file)
{
    if (fclose(file) != 0)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
    file = NULL;
}

char *Strstr(char const *s1, char const *s2)
{
    char *p = strstr(s1, s2);
    if (p == NULL)
    {
        printf("No %s can be find!!!", s2);
        exit(EXIT_FAILURE);
    }
    else if (p == s1)
    {
        perror("Item is null");
        exit(EXIT_FAILURE);
    }
    else
    {
        return p;
    }
}

void *Malloc(size_t size)
{
    void *p = malloc(size);
    if (p == NULL)
    {
        perror("Malloc: Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return p;
    }
}

void *Realloc(void *ptr, size_t new_size)
{
    void *p = realloc(ptr, new_size);
    if (p == NULL)
    {
        perror("Realloc: Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return p;
    }
}

void initAllItem(allItem *allitem)
{
    allitem->base = (char *)Malloc(INIT_LEN * (sizeof(char)));
    allitem->size = INIT_LEN;
}

void saveItem(FILE *file, allItem *allitem)
{
    size_t offset = 0;
    size_t flag;
    do
    {
        if (offset >= allitem->size)
        { //如果读入字符数大于allitem->size,重新申请空间
            allitem->base = (char *)Realloc((void *)allitem->base,
                                            (allitem->size + IC) * (sizeof(char)));
            allitem->size += IC;
        }
        flag = fread(allitem->base + offset,
                     sizeof(char), 1024, file);
        offset += flag;
    } while (flag);
}

void getitemhead(int item_len, char const *item, char *itemhead)
{
    itemhead[0] = '{';
    int i;
    for (i = 0; i <= item_len; i++)
    {
        itemhead[i + 1] = item[i];
    }
    itemhead[i] = ':';
    itemhead[i + 1] = '\0';
}

void getitemtail(int item_len, char const *item, char *itemtail)
{
    int i;
    for (i = 0; i < item_len; i++)
    {
        itemtail[i] = item[i];
    }
    itemtail[i] = '}';
    itemtail[i + 1] = '\0';
}
