// htab_bucket_count.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_bucket_count.c

#include "htab.h"
#include "hash_table_structs.h"

size_t htab_bucket_count(const htab_t * t)
{
    return t->arr_size;
}