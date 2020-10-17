// hash_table_structs.h
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Privatni hlavickovy soubor hash_table_structs.h definujici struktury htab a htab_item deklarovane v htab.h
//
// Poznamky:    Je nutne umistit tento hlavickovy do kazdeho modulu, avsak wordcount.c tento soubor jiz nevyzaduje.

#ifndef __HTAB_STRUCTS_H__
#define __HTAB_STRUCTS_H__

#include "htab.h"

struct htab
{
    unsigned long size;
    unsigned long arr_size;
    struct htab_item* ptr[];
};

struct htab_item
{
    unsigned long data;
    struct htab_item* next;
    char key[];
};

#endif // __HTAB_STRUCTS_H__