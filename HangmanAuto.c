/**
* @autor Mr.Ajay 
* @name Hangman - with auto name generator and respective case-sensitive rules
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define WORDS 10
#define WORDLEN 40
#define CHANCE 6

char *decrypt(char *code) {
    int hash = ((strlen(code) - 3) / 3) + 2;
    char *decrypt = malloc(hash);
    char *toFree = decrypt;
    char *word = code;
    for (int ch = *code; ch != '\0'; ch = *(++code)) {
        if ((code - word + 2) % 3 == 1) {
            *(decrypt++) = ch - (word - code + 1) - hash;
        }
    }
    *decrypt = '\0';
    return toFree;
}

void printHangman(int mistakes) {
    switch (mistakes) {
        case 0:
            printf(" ______________\n");
            printf("|       |       \n");
            printf("|               \n");
            printf("|               \n");
            printf("|               \n");
            printf("|               \n");
            printf("|               \n");
            printf("|===============\n");
            break;
        case 1:
            printf(" ______________\n");
            printf("|       |       \n");
            printf("|   [| o o |]   \n");
            printf("|               \n");
            printf("|               \n");
            printf("|               \n");
            printf("|               \n");
            printf("|===============\n");
            break;
        case 2:
            printf(" ______________\n");
            printf("|       |       \n");
            printf("|   [| o o |]   \n");
            printf("|   [|  ^  |]   \n");
            printf("|               \n");
            printf("|               \n");
            printf("|               \n");
            printf("|===============\n");
            break;
        case 3:
            printf(" ______________\n");
            printf("|       |       \n");
            printf("|   [| o o |]   \n");
            printf("|   [|  ^  |]   \n");
            printf("| <--[|- -|]-->   \n");
            printf("|               \n");
            printf("|               \n");
            printf("|===============\n");
            break;
        case 4:
            printf(" ______________\n");
            printf("|       |       \n");
            printf("|   [| o o |]   \n");
            printf("|   [|  ^  |]   \n");
            printf("| <--[|- -|]-->   \n");
            printf("|   [|_____|]   \n");
            printf("|              \n");
            printf("|==============\n");
            break;
        case 5:
            printf(" ______________\n");
            printf("|       |       \n");
            printf("|   [| o o |]   \n");
            printf("|   [|  ^  |]   \n");
            printf("| <--[|- -|]-->   \n");
            printf("|   [|_____|]   \n");
            printf("|    |     |    \n");
            printf("|===============\n");
            break;
        case 6:
            printf(" ______________\n");
            printf("|       |       \n");
            printf("|   [| o o |]   \n");
            printf("|   [|  ^  |]   \n");
            printf("| <--[|- -|]-->   \n");
            printf("|   [|_____|]   \n");
            printf("|    |     |    \n");
            printf("|===============\n");
            break;
    }
}

int main() {
    srand(time(NULL));

    char values[WORDS][WORDLEN] = {
        "N~mqOlJ^tZletXodeYgs", "gCnDIfFQe^CdP^^B{hZpeLA^hv", "7urtrtwQv{dt`>^}FaR]i]XUug^GI",
        "aSwfXsxOsWAlXScVQmjAWJG", "cruD=idduvUdr=gmcauCmg]", "BQt`zncypFVjvIaTl]u=_?Aa}F",
        "iLvkKdT`yu~mWj[^gcO|", "jSiLyzJ=vPmnv^`N]^>ViAC^z_", "xo|RqqhO|nNstjmzfiuoiFfhwtdh~",
        "OHkttvxdp|[nnW]Drgaomdq"
    };

    char *body = malloc(CHANCE + 1);

    int id = rand() % WORDS;
    char *word = decrypt(values[id]);
    int len = strlen(word);
    char *guessed = malloc(len);
    char falseWord[CHANCE];

    memset(body, ' ', CHANCE + 1);
    memset(guessed, '_', len);
    char guess;
    bool found;
    char *win;
    int mistakes = 0;

    printf("\n\tWelcome to Hangman!\n");
    printf("\tRules:\n");
    printf("\t- Maximum 6 mistakes are allowed.\n");
    printf("\t- All alphabet are in lower case.\n");
    printf("\t- All words are name of very popular Websites. eg. Google\n");
    printf("\t- Syntax : Alphabet\n\n");

    do {
        found = false;
        printf("\n\n");
        printHangman(mistakes);
        printf("\n\n");
        printf("\tMistakes : %d\n", mistakes);
        printf("\tFalse Letters : ");
        if (mistakes == 0)
            printf("None\n");
        for (int i = 0; i < mistakes; ++i) {
            printf("%c", falseWord[i]);
        }
        printf("\n\n");

        for (int i = 0; i < len; ++i) {
            if (guessed[i] == '_')
                printf("_ ");
            else
                printf("%c ", guessed[i]);
        }
        printf("\n\n");

        printf("\tGive me a lowercase alphabet: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        int alreadyGuessed = 0;
        for (int i = 0; i < mistakes; i++) {
            if (falseWord[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }

        if (alreadyGuessed) {
            printf("\tYou have already guessed '%c'\n", guess);
            continue;
        }

        int correctGuess = 0;
        for (int i = 0; i < len; ++i) {
            if (word[i] == guess) {
                found = true;
                guessed[i] = guess;
                correctGuess = 1;
            }
        }

        if (!found) {
            falseWord[mistakes++] = guess;
        }

        win = strchr(guessed, '_');
    } while (mistakes < CHANCE && win != NULL);

    if (win == NULL) {
        printf("\n");
        for (int i = 0; i < len; ++i) {
            printf("%c ", guessed[i]);
        }
        printf("\n\n\tCongratulations! You have won: %s\n\n", word);
    } else {
        printf("\n");
        printHangman(mistakes);
        printf("\n\n\tBetter luck next time. The word was %s\n\n", word);
    }

    free(body);
    free(word);
    free(guessed);
    return EXIT_SUCCESS;
}
