// htab_end.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_end.c

#include "htab.h"
#include "hash_table_structs.h"

htab_iterator_t htab_end(const htab_t * t)
{
    htab_iterator_t iterator;
    iterator.ptr = NULL;
    iterator.t = t;
    iterator.idx = htab_bucket_count(t);
    return iterator;
}