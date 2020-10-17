// htab_iterator_get_key.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_iterator_get_key.c

#include "htab.h"
#include "hash_table_structs.h"

htab_key_t htab_iterator_get_key(htab_iterator_t it)
{
    if (htab_iterator_valid(it))
    {
        return it.ptr->key;
    }
    else
    {
       return NULL;
    }
}