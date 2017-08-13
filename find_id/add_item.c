#include "myid.h"

void addItem(char const *item, char const *name,
             char const *id, char const *password)
{
    FILE *idlist = Fopen(IDLIST, "a");
    int i = fprintf(idlist,
                    "{%s:\nName: %s\nId: %s\nPassword: %s\n%s}\n\n",
                    item, name, id, password, item);
    if (i == 0)
    {
        printf("In fun <addItem>, fprintf");
        fflush(stdout);
    }
    Fclose(idlist);
}
