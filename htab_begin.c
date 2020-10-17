// htab_begin.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_begin.c

#include "htab.h"
#include "hash_table_structs.h"

htab_iterator_t htab_begin(const htab_t * t)
{
    htab_iterator_t iterator;

    for (unsigned long i = 0; i < htab_bucket_count(t); i++)
    {
        if (t->ptr[i] != NULL)
        {
            iterator.ptr = t->ptr[i];
            iterator.t = t;
            iterator.idx = i;
            return iterator;
        }
    }
    return htab_end(t);
}