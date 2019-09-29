/**
 * @file shuffle_functions.c
 * @author 170011474
 * @since March 11th
 * @brief functions for faro_shuffle and output
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "print_faro_val.h"
#include "shuffle.h"
#define BITS_OF_INT 16

int binary_size = 0;

/**
 * @brief Function to return an int array containing the binary number form of the position
 * - keeping dividing position by 2 and recording remainders
 * - reverse the order to store remainders
 * - the result is the binary form of the position
 * 
 * @param int position The value of position is from inputs from users
 * @return int* binary form of the position
 */
int *toBinary(int position)
{
    // this array is to store the remainder
    int arr[BITS_OF_INT]; // since the INT_MAX can be represented by 16 bits
    int i = 0;            // to trace the current index in the arr, also the current length
    while (position > 0)
    {
        int remainder = position % 2;
        arr[i++] = remainder;    // record each remainder after each division
        position = position / 2; // update the position
    }

    int len = i;                          // i represents the current length of arr
    int *res = malloc(len * sizeof(int)); // the real binary number
    binary_size = len;
    // this for loop is to reverse the order of int arr[]
    // store the result into res[]
    for (int j = len - 1; j >= 0; j--)
    {
        res[len - j - 1] = arr[j];
    }
    return res;
}

/**
 * @brief Funtion returns the length of binary array
 * 
 * @return length of binary array, so the it can be used to iterate over the binary array
 *          - Do in-shuffle or out-shuffle depending on the value in the current index
 */
int return_binary_size()
{
    return binary_size;
}

/**
 * @brief Function to turn the decklist into two halves. Store two halves into two decklists respectively.
 * This function uses an index to navigate through the int deck-size
 * 
 * EXAMPLE USAGE:
 *      partition(cards, first_half, second_half, deck_size);
 * 
 * @param Decklist* cards - the current decklist which stores all of cards
 * @param char** first_half - the array of pointers referring to contents of top half cards
 * @param char** second_half - the array of pointer referring to contents of bottom half cards
 * @param int deck_size - the size of the current decklist
 * 
 * @return void
 */
void partition(decklist *cards, char **first_half, char **second_half, int deck_size)
{
    card *current = cards->head;
    int firstIndex = 0;  // index for first_half
    int secondIndex = 0; // index for second_half
    int i = 0;

    while (i < (deck_size / 2))
    { // extracts the top half of cards
        first_half[firstIndex] = current->content;
        firstIndex++;
        current = current->next;
        i++;
    }
    while (current != NULL)
    { // extracts the bottom half of cards
        second_half[secondIndex] = current->content;
        secondIndex++;
        current = current->next;
    }
}

/*
 * @brief Function to inshuffle the decklist
 * the top most card in the original decklist should now be the second card in the current deck list
 * - if the index is even, then extracts a content of card from the second_half array
 * - if the index is odd, then extracts a content of card from the first_half array
 */
void inshuffle(decklist *cards, int deck_size)
{
    char *first_half[deck_size / 2];
    char *second_half[deck_size / 2];
    int firstIndex = 0;
    int secondIndex = 0;
    card *current = cards->head; // as an index of the current decklist

    partition(cards, first_half, second_half, deck_size);

    // iterate over the current decklist to change the content of each card
    for (int i = 0; i < deck_size; i++)
    {
        if (i % 2 == 0)
        { // extracts a card from the second_half decklist
            current->content = second_half[secondIndex];
            secondIndex++;
        }
        else
        {
            current->content = first_half[firstIndex];
            firstIndex++;
        }
        current = current->next; // the next card of the current decklist
    }
}
/* @brief Function to outshuffle the decklist
 * - the top most card in the original decklist is still the top most card
 * - even index: extracts content of a card from the first_half
 * - odd index: extracts content of a card from the second_half
 */
void outshuffle(decklist *cards, int deck_size)
{
    char *first_half[deck_size / 2];
    char *second_half[deck_size / 2];
    int firstIndex = 0; //
    int secondIndex = 0;
    card *current = cards->head; // as an index of the current decklist

    partition(cards, first_half, second_half, deck_size);

    for (int i = 0; i < deck_size; i++)
    {
        if (i % 2 == 0)
        {
            current->content = first_half[firstIndex];
            firstIndex++;
        }
        else
        { // extracts a card from the second_half decklist
            current->content = second_half[secondIndex];
            secondIndex++;
        }
        current = current->next;
    }
}

/**
 * @brief Function to generate stacscheck-compliant output.
 * 
 * This function called once per data-item. There are (2+deck_size) calls
 *  needed to output a deck's data. For example, 52 cards consists of:
 *     - one call for output type (PREFIX_START, PREFIX_IN, PREFIX_OUT)
 *     - 52 calls for the card contents (CARD_VAL)
 *     - one call to terminate the output (SUFFIX)
 * EXAMPLE USAGE:
 *     print_faro_val("", PREFIX_IN); // outputs " IN: "
 *     print_faro_val(card_val, CARD_VAL); // eg. if card_val <-- "5H\0", outputs "5H "
 *     print_faro_val("", SUFFIX);    // OUTPUTS "EoD\n"
 * 
 * @param string A pointer to a string of data (valid w/ CARD_VAL, otherwise ignored).
 * @param output_type Enumerated type (above). Determines type of output. 
 *                    Only CARD_VAL outputs preceding string param.
 * @return void
 */
void print_faro_val(const char *string, enum stringplace output_type)
{
    switch (output_type) // depending on different enum, print out differen contents
    {
    case PREFIX_IN:
        printf("IN : ");
        break;
    case PREFIX_OUT:
        printf("OUT: ");
        break;
    case SUFFIX:
        printf("EoD\n");
        break;
    case CARD_VAL:
        printf("%s ", string);
        break;
    default:
        break;
    }
}

/**
 * @brief Function to print the current decklist
 * This function needs to print out the prefix and suffix properly
 * - print out "IN : " or "OUT: " depending on the argument
 * - if in is 1, then print out the decklist after an in-shuffle
 * - if in is 0, then print out the decklist after an out-shuffle
 * - iterate over the whole decklist to print out the content
 * 
 * EXAMPLE USAGE: print_all(cards, 1);
 * 
 * @param decklist* cards - the current decklist holding all cards
 * @parma int in - determine whether the decklist is after in-shuffle or out-shuffle
 * @return void
 */
void print_all(decklist *cards, int in)
{
    if (in) // if the decklist is after an in-shuffle
        print_faro_val("", PREFIX_IN);
    else // if the decklist is after an out-shuffle
        print_faro_val("", PREFIX_OUT);

    card *current = cards->head;
    while (current != NULL) // iterate over the decklist to print out all cards
    {
        print_faro_val(current->content, CARD_VAL);
        current = current->next;
    }

    print_faro_val("", SUFFIX); // print out the suffix
}

/**
 * @brief Function to do all shuffles depending on the binary number of the position
 * - This function iterates over the int array which holds the binary number of the position
 * - if 1, then in-shuffle
 * - if 0, then out-shuffle
 * - print out contents of the decklist after each shuffle
 * 
 * @param int* binary - for example, position 6 is converted into {1, 1, 0} here
 * @param int binary_size - the length of the array
 * @param decklist* cards - the current decklist
 * @param int deck_size - the size of the current decklist
 * 
 * @return void
 */
void shuffle(int *binary, int binary_size, decklist *cards, int deck_size)
{
    for (int i = 0; i < binary_size; i++)
    {
        if ((binary[i]) == 1) // loop over the binary form the position
        {                     // 1 is for in-shuffle
            inshuffle(cards, deck_size);
            print_all(cards, 1);
        }
        else // 0 is for out-shuffle
        {
            outshuffle(cards, deck_size);
            print_all(cards, 0);
        }
    }
}
