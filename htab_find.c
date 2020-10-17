// htab_find.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_find.c

#include "htab.h"
#include "hash_table_structs.h"
#include <string.h>

htab_iterator_t htab_find(htab_t * t, htab_key_t key)
{
    size_t index = htab_hash_fun(key) % htab_bucket_count(t);
    
    htab_iterator_t iterator;
    iterator.ptr = t->ptr[index];
    iterator.t = t;
    iterator.idx = index;

    if (iterator.ptr == NULL)   // Na danem indexu neni zadny zaznam
    {
        return htab_end(t);
    }

    while (iterator.ptr->next != NULL)  // Prohledavani a porovnavani klicu zaznamu na danem indexu
    {
        if (strcmp(iterator.ptr->key, key) == 0)
        {
            return iterator;
        }
        iterator.ptr = iterator.ptr->next;
    }

    if (strcmp(iterator.ptr->key, key) == 0)      // Porovnani klice posledniho zaznamu na indexu
    {
        return iterator;
    }

    return htab_end(t);
}