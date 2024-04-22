/**
* @autor Mr.Ajay Tokala
* @name Hangman - With manual addition of keywords without rule conditions
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Words list
char *words[] = {"apple", "banana", "orange", "grape", "strawberry"};
int num_words = 5;

// Function prototypes
void printHangman(int);
int chooseRandomWord(char *, int);
int checkGuess(char, char *, char *);

int main() {
    srand(time(NULL));

    char word[50];
    char guessed[50];
    char letter;
    int attempts = 6;
    int word_length;
    int i, found, gameover;

    // Choose a random word
    chooseRandomWord(word, num_words);

    // Initialize guessed array
    word_length = strlen(word);
    for (i = 0; i < word_length; i++)
        guessed[i] = '_';
    guessed[i] = '\0';

    printf("Welcome to Hangman!\n");

    while (attempts > 0) {
        gameover = 1;
        printHangman(attempts);
        printf("Word: %s\n", guessed);
        printf("Guess a letter: ");
        scanf(" %c", &letter);

        found = checkGuess(letter, word, guessed);

        if (!found) {
            attempts--;
            printf("Incorrect guess!\n");
        } else {
            printf("Correct guess!\n");
        }

        for (i = 0; i < word_length; i++) {
            if (guessed[i] == '_') {
                gameover = 0;
                break;
            }
        }

        if (gameover) {
            printf("Congratulations! You guessed the word: %s\n", word);
            break;
        }
    }

    if (attempts == 0)
        printf("Sorry, you've run out of attempts. The word was: %s\n", word);

    return 0;
}

// Print the hangman based on the number of attempts remaining
void printHangman(int attempts) {
    switch (attempts) {
        case 6:
            printf("\n");
            printf(" ______________\n");
            printf("|       |       \n");
            printf("|               \n");
            printf("|               \n");
            printf("|               \n");
            printf("|               \n");
            printf("|               \n");
            printf("|===============\n");
            break;
        case 5:
            printf("\n");
            printf(" ______________\n");
            printf("|       |       \n");
            printf("|   [| o o |]   \n");
            printf("|               \n");
            printf("|               \n");
            printf("|               \n");
            printf("|               \n");
            printf("|===============\n");
            break;
        case 4:
            printf("\n");
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
            printf("\n");
            printf(" ______________\n");
            printf("|       |       \n");
            printf("|   [| o o |]   \n");
            printf("|   [|  ^  |]   \n");
            printf("| <--[|- -|]-->   \n");
            printf("|               \n");
            printf("|               \n");
            printf("|===============\n");
            break;
        case 2:
            printf("\n");
            printf(" ______________\n");
            printf("|       |       \n");
            printf("|   [| o o |]   \n");
            printf("|   [|  ^  |]   \n");
            printf("| <--[|- -|]-->   \n");
            printf("|   [|_____|]   \n");
            printf("|              \n");
            printf("|==============\n");
            break;
        case 1:
            printf("\n");
            printf(" ______________\n");
            printf("|       |       \n");
            printf("|   [| o o |]   \n");
            printf("|   [|  ^  |]   \n");
            printf("| <--[|- -|]-->   \n");
            printf("|   [|_____|]   \n");
            printf("|    |     |    \n");
            printf("|===============\n");
            break;
        case 0:
            printf("\n");
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

// Choose a random word from the words list
int chooseRandomWord(char *word, int num_words) {
    int index = rand() % num_words;
    strcpy(word, words[index]);
    return index;
}

// Check if the guessed letter is in the word
int checkGuess(char letter, char *word, char *guessed) {
    int i, found = 0;
    for (i = 0; word[i] != '\0'; i++) {
        if (word[i] == letter) {
            guessed[i] = letter;
            found = 1;
        }
    }
    return found;
}
