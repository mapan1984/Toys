#include "myid.h"

void delItem(char const *item)
{
    // 从旧文件读取
    FILE *idlist = Fopen(IDLIST, "r");
    allItem allitem;
    initAllItem(&allitem);
    saveItem(idlist, &allitem);
    Fclose(idlist);

    char itemhead[10];
    char itemtail[10];
    int item_len = strlen(item);
    getitemhead(item_len, item, itemhead);
    getitemtail(item_len, item, itemtail);

    char *head = Strstr(allitem.base, itemhead);
    char *tail = Strstr(head + item_len + 2, itemtail);
    while (head <= (tail + item_len + 2))
    {
        *head = '\0';
        head++;
    }

    // 写入新文件
    FILE *newidlist = Fopen(IDLIST, "w");
    int allitem_len = strlen(allitem.base);
    fwrite(allitem.base, sizeof(char), allitem_len, newidlist);
    free(allitem.base);
    Fclose(newidlist);
}
