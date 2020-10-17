// htab_iterator_valid.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_iterator_valid.c

#include "htab.h"
#include "hash_table_structs.h"
#include <stdbool.h>

bool htab_iterator_valid(htab_iterator_t it)
{
    return it.ptr!=NULL;
}