// io.c
// Reseni IJC-DU2, priklad 2), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro modul io, ziskavajic slovo z pridaneho streamu

#include "io.h"
#include <stdio.h>
#include <ctype.h>

// 0 Znazornuje false, 1 znazornuje true
static int foundLongerWord = 0;

// Vraci delku nacteneho slova do parametru s
// Vraci EOF pri nalezneti EOF
// Je mozne, ze vrati EOF i pri nacteni slova do parametru s
// Nutna kontrola pri volani
int get_word(char *s, int max, FILE *f)
{
    int c;
    // Preskoceni bilych znaku na zacatku streamu
    while((c = getc(f)) != EOF && isspace(c))
    {
        ;
    }

    // Kontrola, zda nebyl jiz nalezen EOF
    if (c == EOF)
    {
        return EOF;
    }

    ungetc(c, f);
    int counter = 0;
    // Nacitani maximalne max znaku
    while((c = getc(f)) != EOF && !isspace(c) && counter < max)
    {
        s[counter] = c;
        counter++;
    }

    // Kontrola, zda nebyl jiz nalezen EOF
    if (c == EOF)
    {
        return EOF;
    }

    // Kontrola zda se nejedna o delsi slovo nez max
    // V pripade, ze ano, slovo se "zkrati" (preskoci ve streamu)
    if (!isspace(c))
    {
        if (!foundLongerWord)
        {
            fprintf(stderr, "CHYBA: io.c: Nalezeno delsi slovo, probehlo zkraceni.\n");
            foundLongerWord = 1;
        }

        while((c = getc(f)) != EOF && !isspace(c))
        {
            ;
        }
        if (c == EOF)
        {
            return EOF;
        }

        ungetc(c, f);
    }

    // Pridani NULL charakteru a vraceni delky stringu
    s[counter] = '\0';
    return counter;
}