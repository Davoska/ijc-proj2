// wordcount.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro program wordcount
//
// Poznamky:    Soubor vyuziva tabulku s rozptylenymi polozkami (hash table)

#include "htab.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>

// Vybrani velikosti tabulky s rozptylenymi polozkami zalezi na poctu klicu, ktere ocekavame v analyzovanem textu.
// Vyuzil jsem data ze stranky http://www.tylervigen.com/literature-statistics pro ziskani poctu unikatnich slov
// v anglictine v knihach - The Hobbit by JRR Tolkien, A Tale of Two Cities by Charles Dickens, ...
// Pocet prumernych unikatnich slov jsem vynasobil cislem 1.3 pro zmenseni pravdepodobnosti koliz pri pridavani polozek.
// Jako vysledne cislo jsem vybral nejblizsi prvocilo pro zmenseni pravdepodobnosti kolizi.
// HAST_TABLE_SIZE = NEXT_PRIME_NUMBER_AFTER(AVERAGE_UNIQUE_WORDS_COUNT * 1.3)
#define HAST_TABLE_SIZE (8147)
#define MAX_WORD_LENGTH 127

int main()
{
    // Inicializace hash-tabulky
    htab_t* m = htab_init(HAST_TABLE_SIZE);
    if (m == NULL)
    {
        fprintf(stderr, "CHYBA: wordcount.c: Neuspesna alokace pameti.\n");
        return 1;
    }

    // Alokace mista pro ukladani pomocneho retezce
    htab_iterator_t it;
    char* word = malloc(sizeof(char) * (MAX_WORD_LENGTH + 1));
    if (word == NULL)
    {
        fprintf(stderr, "CHYBA: wordcount.c: Neuspesna alokace pameti.\n");
        free(m);
        return 1;
    }
    
    // Nacitani slov (sekvence nebilych symbolu, zakoncena bylim symbolem) do hash-tabulky
    while(get_word(word, MAX_WORD_LENGTH, stdin) != EOF)
    {
        it = htab_find(m, word);        // Kontrola, zda jiz je klic ulozen v tabulce
        if (htab_iterator_valid(it))    // V pripade naleznuti klice, nasleduje inkrementace poctu klice
        {
            htab_iterator_set_value(it, (htab_iterator_get_value(it) + 1));
        }
        else                            // V pripade nenaleznuti, vytvari se zaznam s danym klicem a nasleduje inkrementace
        {
            it = htab_lookup_add(m, word);
            if (!htab_iterator_valid(it))
            {
                fprintf(stderr, "CHYBA: wordcount.c: Neuspesna alokace pameti.\n");
                free(word);
                htab_free(m);
                return 1;
            }
            htab_iterator_set_value(it, 1);
        }
    }

    // Vypsani dat vsech zaznamu v tabulce ve formatu:  "klic    pocet_naleznuti"
    for (it = htab_begin(m); htab_iterator_valid(it); it = htab_iterator_next(it))
    {
        printf("%s\t%d\n", htab_iterator_get_key(it), htab_iterator_get_value(it));
    }

    // Dealokace mista z haldy
    free(word);
    htab_free(m);
    return 0;
}