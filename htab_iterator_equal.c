// htab_iterator_equal.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_iterator_equal.c

#include "htab.h"
#include "hash_table_structs.h"
#include <stdbool.h>

bool htab_iterator_equal(htab_iterator_t it1, htab_iterator_t it2)
{
    return it1.ptr==it2.ptr && it1.t == it2.t;
}