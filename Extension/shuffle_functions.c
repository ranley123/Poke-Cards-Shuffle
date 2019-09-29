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

int return_binary_size()
{
    return binary_size;
}

/*
 * @brief Function to turn the decklist into two halves. Store two halves into two decklists respectively.
 */
void partition(decklist *cards, decklist *first_half, decklist *second_half, int deck_size)
{
    int i = 0; // index of decklist* cards
    card *current = cards->head;

    while (i < (deck_size / 2))
    { // extracts the top half of cards
        addCard(first_half, current->content);
        current = current->next;
        i++;
    }
    while (current != NULL)
    { // extracts the bottom half of cards
        addCard(second_half, current->content);
        current = current->next;
    }
}

/*
 * @brief Function to inshuffle the decklist
 * the top most card in the original decklist should now be the second card in the current deck list
 * - if the index is even, then extracts a card from the second_half decklist
 * - if the index is odd, then extracts a card from the first_half decklist
 */
void inshuffle(decklist *cards, int deck_size)
{
    decklist *first_half = makeDecklist();
    decklist *second_half = makeDecklist();
    card *current_first = NULL;         // as an index of the decklist* first_half
    card *current_second = NULL;        // as an index of the decklist* second_half
    card *current = cards->head; // as an index of the current decklist

    partition(cards, first_half, second_half, deck_size);

    current_first = first_half->head;
    current_second = second_half->head;

    // iterate over the current decklist to change the content of each card
    for (int i = 0; i < deck_size; i++)
    {
        if (i % 2 == 0)
        { // extracts a card from the second_half decklist
            current->content = current_second->content;
            current_second = current_second->next; // update to the next card in the decklist second_half
        }
        else
        {
            current->content = current_first->content;
            current_first = current_first->next; // update to the next card in the decklist first_half
        }
        current = current->next; // the next card of the current decklist
    }
    free(first_half);
    free(second_half);
}
/* @brief Function to outshuffle the decklist
 * - the top most card in the original decklist is still the top most card
 * - even index: extracts a card from the first_half
 * - odd index: extracts a card from the second_half
 */
void outshuffle(decklist *cards, int deck_size)
{
    decklist *first_half = makeDecklist();
    decklist *second_half = makeDecklist();
    card *current_first = NULL;         // as an index of the decklist* first_half
    card *current_second = NULL;        // as an index of the decklist* second_half
    card *current = cards->head; // as an index of the current decklist

    partition(cards, first_half, second_half, deck_size);

    current_first = first_half->head;
    current_second = second_half->head;

    for (int i = 0; i < deck_size; i++)
    {
        if (i % 2 == 0)
        {
            current->content = current_first->content;
            current_first = current_first->next;
        }
        else
        { // extracts a card from the second_half decklist
            current->content = current_second->content;
            current_second = current_second->next;
        }
        current = current->next;
    }

    free(first_half);
    free(second_half);
}


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

/*
 * @brief Function to print the current decklist
 * 
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

/*
 * @brief Function to do all shuffles depending on the binary number of the position
 * - This function iterates over the int array which holds the binary number of the position
 * - if 1, then in-shuffle
 * - if 0, then out-shuffle
 * - print out contents of the decklist after each shuffle
 */
void shuffle(int *binary, int binary_size, decklist *cards, int deck_size)
{
    for (int i = 0; i < binary_size; i++)
    {
        if ((binary[i]) == 1) // loop over the binary form the position
        { // 1 is for in-shuffle
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