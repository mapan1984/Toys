#include "myid.h"

static void getInfo(char *item, char *name, char *id, char *password);
static void getItem(char *item);

int main(int argc,char **argv){
    char item[10];
    printf("\nAdd or Delete or Find, please input 'a' or 'd' or 'f': ");
    char m = getchar();
    if(m == 'a'){  /* Add item */
        char name[10], id[20], password[20];
        getInfo(item, name, id, password);
        addItem(item, name, id, password);
        printf("%s has add..", item);
    }else if(m == 'f'){ /* Find item */
        getItem(item);
        findItem(item);
    }else if(m == 'd'){ /* Del item */
        getItem(item);
        delItem(item);
        printf("%s has del..", item);
    }else{
        puts(" Error!! Please input 'a' or 'f' or 'd' or 'q' !!");
        exit(EXIT_FAILURE);
    }
    return 0;
}

static void getInfo(char *item, char *name, char *id, char *password){
    puts("item: ");
    scanf("%s", item);
    puts("name: ");
    scanf("%s", name);
    puts("id: ");
    scanf("%s", id);
    puts("password: ");
    scanf("%s", password);
}

static void getItem(char *item){
    printf("dou you want to: ");
    scanf("%s", item);
}
