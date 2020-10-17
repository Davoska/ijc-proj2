// htab_erase.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_erase.c

#include "htab.h"
#include "hash_table_structs.h"
#include <stdlib.h>

void htab_erase(htab_t * t, htab_iterator_t it)
{
    // Iterator je neplatny
    if (htab_iterator_equal(it, htab_end(t)))
    {
        return;
    }

    // Bucket ukazuje na zadany htab_item_t
    if (it.ptr == it.t->ptr[it.idx])
    {
        htab_iterator_t temp;
        temp.ptr = it.ptr->next;
        free(it.t->ptr[it.idx]);
        t->ptr[it.idx] = temp.ptr;
        t->size = t->size - 1;
        return;
    }

    // Iterator ukazuje na htab_item_t v indexu, kde se vyskytuje vice htab_item_t
    htab_iterator_t itPrev;
    itPrev.t = it.t;
    itPrev.ptr = it.t->ptr[it.idx];
    itPrev.idx = it.idx;
    while (itPrev.ptr->next != it.ptr)
    {
        itPrev.ptr = itPrev.ptr->next;
    }

    t->size = t->size - 1;
    itPrev.ptr->next = it.ptr->next;
    free(it.ptr);
    return;
}