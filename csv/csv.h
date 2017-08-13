#ifndef _CSV_H_
#define _CSV_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* csv.h: interface for csv library */
extern char *csvgetline(FILE *f);  // read next input line
extern char *csvfiled(int n);  // return field n
extern int csvnfiled(void);  // return number of fields

#endif
