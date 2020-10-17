// htab_iterator_set_value.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul htab_iterator_set_value.c

#include "htab.h"
#include "hash_table_structs.h"

htab_value_t htab_iterator_set_value(htab_iterator_t it, htab_value_t val)
{
   if (htab_iterator_valid(it))
   {
        it.ptr->data = val;
        return 0;
   }
   else
   {
       return 1;
   }  
}