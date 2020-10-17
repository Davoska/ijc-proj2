// htab_init.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_init.c

#include "htab.h"
#include "hash_table_structs.h"
#include <stdlib.h>

htab_t *htab_init(size_t n)
{
    htab_t* ptr = malloc(sizeof(htab_t) + n * sizeof(struct htab_item));

    if (ptr != NULL)
    {
        ptr->arr_size = n;
        ptr->size = 0;

        for (unsigned long i = 0; i < n; i++)
        {
            ptr->ptr[i] = NULL;
        }
    }

    return ptr;
}