// htab_lookup_add.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_lookup_add.c

#include "htab.h"
#include "hash_table_structs.h"
#include <string.h>
#include <stdlib.h>

htab_iterator_t htab_lookup_add(htab_t * t, htab_key_t key)
{
    // Kontrola, zda iterator opravdu neexistuje
    htab_iterator_t iterator = htab_find(t, key);
    if (htab_iterator_valid(iterator))
    {
        return iterator;
    }

    size_t index = htab_hash_fun(key) % htab_bucket_count(t);
    iterator.ptr = t->ptr[index];
    iterator.t = t;
    iterator.idx = index;

    // Vytvoreni zaznamu
    if (iterator.ptr == NULL)   // Vytvoreni prvniho zaznamu na danem indexu
    {
        iterator.ptr = malloc(sizeof(struct htab_item) + (strlen(key) + 1) * sizeof(char));
        if (iterator.ptr == NULL)
        {
            return htab_end(t);
        }

        strcpy(iterator.ptr->key, key);
        t->ptr[index] = iterator.ptr;
    }
    else                        // Vytvoreni n-teho zaznamu na danem indexu   
    {
        while (iterator.ptr->next != NULL)
        {
            iterator.ptr = iterator.ptr->next;
        }

        iterator.ptr->next = malloc(sizeof(struct htab_item) + (strlen(key) + 1) * sizeof(char));
        if (iterator.ptr->next == NULL)
        {
            return htab_end(t);
        }

        strcpy(iterator.ptr->next->key, key);
        iterator.ptr = iterator.ptr->next;
    }
    
    t->size += 1;
    iterator.ptr->next = NULL;
    iterator.ptr->data = 0;
    return iterator;
}