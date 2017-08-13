#include <stdarg.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

/* pack: pack binary items into buf, return length */
int pack(uchar *buf, char *fmt, ...)
{
    va_list args;
    char *p;  // fmt

    uchar *bufp;
    ushort s;
    ulong l;

    bufp = buf;
    va_start(args, fmt);
    for (p = fmt; *p != '\0'; p++) {
        switch (*p) {
            case 'c':  // char
                *bufp++ = va_arg(args, int);
                break;
            case 's':  // short
                s = va_arg(args, int);
                *bufp++ = s >> 8;
                *bufp++ = s;
                break;
            case 'l':  // long
                l = va_arg(args, ulong);
                *bufp++ = l >> 24;
                *bufp++ = l >> 16;
                *bufp++ = l >> 8;
                *bufp++ = l;
                break;
            default:  // illegal type character
                va_end(args);
                return -1;
        }
    }
    va_end(args);
    return bufp - buf;
}

/* pack_type1: pack format 1 packet */
int pack_type1(uchar *buf, ushort count, uchar val, ulong data)
{
    return pack(buf, "cscl", 0x01, count, val, data);
}

/* unpack: unpack packed items from buf, return length */
int unpack(uchar *buf, char *fmt, ...)
{
    va_list args;

    char *p;

    uchar *bufp;

    uchar *pc;
    ushort *ps;
    ulong *pl;

    bufp = buf;
    va_start(args, fmt);
    for (p = fmt; *p != '\0'; p++) {
        switch (*p) {
            case 'c':  // char
                pc = va_arg(args, uchar*);
                *pc = *bufp++;
                break;
            case 's':  // short
                ps = va_arg(args, ushort*);
                *ps = *bufp++ << 8;
                *ps |= *bufp++;
                break;
            case 'l':  // long
                pl = va_arg(args, ulong*);
                *pl = *bufp++ << 24;
                *pl |= *bufp++ << 16;
                *pl |= *bufp++ << 8;
                *pl |= *bufp++;
                break;
            default:  // illegal type character
                va_end(args);
                return -1;
        }
    }
    va_end(args);
    return bufp-buf;
}

int unpack_type0(int n, uchar *buf)
{
}

int unpack_type1(int n, uchar *buf)
{
}

/* unpack_type2: unpack and process type 2 packet */
int unpack_type2(int n, uchar *buf)
{
    uchar c;
    ushort count;
    ulong dw1, dw2;

    if (unpack(buf, "csll", &c, &count, &dw1, &dw2) != n) {
        return -1;
    }

    assert(c == 0x02);
    return process_type2(count, dw1, dw2);
}


int (*unpackfn[])(int, uchar *) = {
    unpack_type0,
    unpack_type1,
    unpack_type2,
};
