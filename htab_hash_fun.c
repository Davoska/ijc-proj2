// htab_hash_fun.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_hash_fun.c

#include "htab.h"

size_t htab_hash_fun(const char *str) {
    unsigned long h = 0;
    const unsigned char *p;
    for (p = (const unsigned char*)str; *p!='\0'; p++)
        h = 65599 * h + *p;
    return h;
}