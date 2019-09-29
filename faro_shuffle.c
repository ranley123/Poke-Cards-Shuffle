#include "shuffle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void read_line(char *str, int cur_size);
void free_all(decklist *cards);

int main(int argc, char *argv[])
{
  // check the validality of arguments
  if (argc != 2)
  {
    printf("Usage: ./faro_shuffle <arg> \n");
    exit(0);
  }

  if (!(strcmp(argv[1], "RANKSUIT") == 0 ||
        strcmp(argv[1], "NUMERICAL") == 0))
  {
    printf("Usage: <arg> must be RANKSUIT or NUMERICAL \n");
    exit(0);
  }

  while (1)
  {
    decklist *cards = makeDecklist();
    int deck_size = 0;
    int position = 0;
    int *binary = NULL;    // the int array stores the binary number of position
    int binary_size = 0;   // the length of the int array
    int temp_size = 0;     // the initial assumption about the memory size for inputs
    char *input = NULL;    // the inputs of cards
    char *delimiter = " "; // used to separate the input into many tokens
    char *token = NULL;    // each token represents the value of a card

    scanf("%d", &deck_size);
    if (deck_size == -1)
      exit(0);

    scanf("%d", &position);

    temp_size = deck_size * 2; // initlal memory size, assuming it is 2*decksize
    input = (char *)malloc(temp_size * sizeof(char));
    read_line(input, temp_size);

    token = strtok(input, delimiter);
    while (token != NULL)
    {
      addCard(cards, token);
      token = strtok(NULL, delimiter);
    }

    binary = toBinary(position);
    binary_size = return_binary_size();
    shuffle(binary, binary_size, cards, deck_size);

    free(binary);
    free(input);
    free_all(cards);
  }
  return 0;
}

/**
 * @brief Function to read inputs from stdin into a string temp
 * This function uses getchar(), and skip '\n', record any other character in the char*
 * - if the real size is larger than the initial assumption, then use realloc() to expand
 * - after reading all characters, appending a '\0' to indicate ending
 * 
 * @param char* temp Read all card values into this single string
 * @param int size The current length of char *temp
 * 
 * @return void
 */
void read_line(char *input, int size)
{
  int c = 0;
  int index = 0; // index of the char* temp
  c = getchar(); // since the first character is '\n', we need to consume it

  while ((c = getchar()) != EOF)
  {
    if (c == '\n')
      break;
    if (index == size - 1) // indicates that the current memory size is not enough
    {
      input = (char *)realloc(input, (size + 1) * sizeof(char)); // allocate one more character space
      size += 1;                                                 // current length increments
    }
    input[index] = c;
    index++;
  }
  input[index] = '\0'; // append the ending
}

/**
 * @brief Function to free all cards and those related to cards
 * @param decklist* cards - the current decklist needing free()
 * @return void
 */
void free_all(decklist *cards)
{
  card *cur, *next;
  cur = cards->head;
  while (cur)
  {
    next = cur->next;
    free(cur->content); // need to free its content which has been malloc() previously
    free(cur);
    cur = next;
  }
  free(cards);
}
