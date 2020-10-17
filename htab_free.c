// htab_free.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_free.c

#include "htab.h"
#include "hash_table_structs.h"
#include <stdlib.h>

void htab_free(htab_t * t)
{
    htab_clear(t);
    free(t);
}