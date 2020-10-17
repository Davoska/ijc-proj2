// htab_clear.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_clear.c

#include "htab.h"
#include "hash_table_structs.h"

void htab_clear(htab_t * t)
{
    htab_iterator_t it = htab_begin(t);
    htab_iterator_t itNext;
    while (htab_iterator_valid(it))
    {
        itNext = htab_iterator_next(it);
        htab_erase(t, it);
        it = itNext;
    }
    return;
}