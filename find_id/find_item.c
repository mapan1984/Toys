#include "myid.h"

void findItem(char const *item)
{
    FILE *idlist = Fopen(IDLIST, "r");
    allItem allitem;
    initAllItem(&allitem);
    saveItem(idlist, &allitem);
    Fclose(idlist);

    /* {item: item} */
    char itemhead[10];
    char itemtail[10];
    int item_len = strlen(item);
    getitemhead(item_len, item, itemhead);
    getitemtail(item_len, item, itemtail);

    char *head = Strstr(allitem.base, itemhead) + item_len + 2;
    char *tail = Strstr(head, itemtail);
    for (; head < tail; head++)
    {
        putchar(*head);
    }
    free(allitem.base);
}
