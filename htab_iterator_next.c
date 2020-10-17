// htab_iterator_next.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_iterator_next.c

#include "htab.h"
#include "hash_table_structs.h"

htab_iterator_t htab_iterator_next(htab_iterator_t it)
{
    if (it.ptr->next != NULL)
    {
        it.ptr = it.ptr->next;
        return it;
    }

    for (unsigned long i = it.idx + 1; i < htab_bucket_count(it.t); i++)
    {
        if (it.t->ptr[i] != NULL)
        {
            it.ptr = it.t->ptr[i];
            it.idx = i;
            return it;
        }
    }

    return htab_end(it.t);
}