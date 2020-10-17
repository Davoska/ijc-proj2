// tail.c
// Reseni IJC-DU2, priklad 1), 10. 4. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro vytisk poslednich N radku
//
// Poznamky:	Nutna implementace jednorozmerneho pole pro retezce pro zpracovani textu z pripadneho stdin.
//				Je mozna pripadna optimilizace - shiftovat doleva pouze ukazatele na char v poli a ne aktualni retezce.

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

// Pocet znaku povolen na radku (newline se nepocita)
#define LINE_LENGTH 1023

// Vytiskne N retezcu ulozenych poli array
void printArrayOfLines(char *array, unsigned long size)
{
	for (unsigned long i = 0; i < size; i++)
	{
		printf("%s\n", array + i * (LINE_LENGTH + 1));
	}
}

// Alokuje misto na pameti pro N * 1024 bajtu
// Nutna implementace pro pripad vlozeni textu na stdin a tim padem znemozneni dvojite analyzy textu
char *allocNLines(unsigned long N)
{
	return malloc(N * (LINE_LENGTH + 1) * sizeof(char));
}

// Posune kazdy retezec v pole o jedno doleva
// Umozneni ukladani poslednich N radku
void shiftLines(char * array, unsigned long size)
{
	for (unsigned long i = 1; i < size; i++)
	{
		strcpy(array + i * (LINE_LENGTH + 1) - (LINE_LENGTH + 1), array + i * (LINE_LENGTH + 1));
	}
}

// Nacte do pole polsednich N radku (max 1023 znaku + '\0' znak)
// Nastavi hodnotu linesRead predanou odkazem, nutne pro prijeti mene radku nez N radku, na pocet prectenych radku
char *getLastNLines(FILE *stream, unsigned long N, int *linesRead)
{
	char * arrayOfLines = allocNLines(N);
	if (arrayOfLines == NULL)
	{
		return NULL;
	}

	int c = 0;
	int startShifting = 0;
	int currentCharIndex = 0;
	unsigned long currentLine = 0;
	while((c = getc(stream)) != EOF)
	{
			if (c == '\n')
			{
				
				if (startShifting == 1)
				{
					shiftLines(arrayOfLines, N);
					arrayOfLines[currentLine * (LINE_LENGTH + 1) + currentCharIndex] = '\0';
				}
				else
				{
					arrayOfLines[currentLine * (LINE_LENGTH + 1) + currentCharIndex] = '\0';
				}
				
				if (currentLine == N - 1)
				{
					startShifting = 1;
				}
				else
				{
					currentLine++;
				}

				*linesRead += 1;
				currentCharIndex = 0;
			}
			else
			{
				if (startShifting == 1)
				{
					shiftLines(arrayOfLines, N);
					startShifting = 0;
				}

				if (currentCharIndex == LINE_LENGTH)
				{
					fprintf(stderr, "CHYBA: Delka radku je vetsi nez %d symbolu.\n", LINE_LENGTH);
				}
				
				if (currentCharIndex < LINE_LENGTH)
				{
					arrayOfLines[currentLine * (LINE_LENGTH + 1) + currentCharIndex] = c;
				}

				currentCharIndex++;
			}
	}

	return arrayOfLines;
}

// Vytiskne veskere radky od Nteho radku
// Tiskne maximalne 1023 znaku pro jeden radek, pri vice znacich oznami chybu a nasledujici znaky na radku ignoruje
void printLinesFromLineN(FILE *stream, int nthLine)
{
	int c = 0;
	int currentLine = 1;
	int currentCharIndex = 0;
	while ((c = getc(stream)) != EOF)
	{
		if (c == '\n')
		{
			if (currentLine >= nthLine)
			{
				putchar(c);
			}
			currentLine++;
			currentCharIndex = 0;
		}
		else if (currentLine >= nthLine)
		{
			if (currentCharIndex == LINE_LENGTH)
			{
				fprintf(stderr, "CHYBA: Delka radku je vetsi nez %d symbolu.\n", LINE_LENGTH);
			}
			
			if (currentCharIndex < LINE_LENGTH)
			{
				putchar(c);
			}
			currentCharIndex++;
		}
	}
}

int main(int argc, char *argv[])
{
	int opt;
	char *ptr = "";
	int onlyPrintFromNthLine = 0;
	int numberOfLines = 10;

	// Zpracovani argumentu
	while((opt = getopt(argc, argv, ":n:")) != -1)
	{
		switch(opt)
		{
			case 'n':
				numberOfLines = (int)strtod(optarg, &ptr);
				if (strcmp(ptr, "") || numberOfLines <= 0)
				{
					fprintf(stderr, "CHYBA: Nastaveni -n vyzaduje platne kladne cislo\n");
					return 1;
				}

				if (optarg[0] == '+')
				{
						onlyPrintFromNthLine = 1;
				}
				break;
			case ':':
				fprintf(stderr, "CHYBA: Nastaveni -n vyzaduje argument\n");
				return 1;
				break;
			case '?':
				fprintf(stderr, "CHYBA: Nezname nastaveni\n");
				return 1;
				break;
		}
	}

	if (argc - optind > 1)
	{
		fprintf(stderr, "CHYBA: Spatny pocet argumentu\n");
		return 1;
	}

	FILE *stream = NULL;
	if (optind < argc)
	{
		stream = fopen(argv[optind], "r");
	}
	else
	{
		stream = stdin;
	}

	if (stream == NULL)
	{
		fprintf(stderr, "CHYBA: Vyskytla se chyba pri cteni souboru\n");
		return 1;
	}

	// Vytisk radku dle zadanych argumentu
	if (onlyPrintFromNthLine == 1)
	{
		// Vytisk vsech radku od N-teho radku
		printLinesFromLineN(stream, numberOfLines);
	}
	else
	{
		// Vytisk poslednich N-radku
		int linesRead = 0;
		char * arrayOfLines = getLastNLines(stream, numberOfLines, &linesRead);

		if (arrayOfLines == NULL)
		{
			fprintf(stderr, "CHYBA: Vyskytla se chyba pri alokaci pameti\n");
			return 1;	
		}

		if (linesRead < numberOfLines)
		{
			numberOfLines = linesRead;
		}

		printArrayOfLines(arrayOfLines, numberOfLines);
		free(arrayOfLines);
	}

	fclose(stream);
	return 0;
}
