#include <stdio.h>
#include <stdlib.h>

int save_byte(void *buf, void *data, int len)
{
    unsigned char *pb = (unsigned char*)buf;
    unsigned char *pd = (unsigned char*)data;
    int i;
    for (i = 0; i < len; i++, pb++, pd++) {
        *pb = *pd;
    }
    return i;
}

void show_byte(void *buf, int len)
{
    unsigned char *pb = (unsigned char*)buf;
    int i;
    for (i = 0; i < len; i++) {
        printf("[%2x] ", pb[i]);
    }
    puts("");
}

int main()
{
    unsigned long l = 0x0807060504030201ul;
    show_byte(&l, sizeof(l));

    unsigned char *buf = (unsigned char*)malloc(sizeof(unsigned long));
    show_byte(buf, sizeof(l));

    save_byte(buf, &l, sizeof(l));
    show_byte(buf, sizeof(l));

    /*
    *buf++ = l >> 56;
    *buf++ = l >> 48;
    *buf++ = l >> 40;
    *buf++ = l >> 32;
    *buf++ = l >> 24;
    *buf++ = l >> 16;
    *buf++ = l >> 8;
    *buf++ = l;
    */

    return 0;
}
