/**
 * @file: shuffle.h
 * @brief: This header file contains function prototypes from shuffle_functions.c
 * @author: 170011474
 * @since: March 11th
 * 
 */

#include "node.h"

/**
 * @brief Function to return an int array containing the binary number form of the position
 * This function is to convert the value of position from octal form to binary form
 * - place the binary bits into an array so they can be read one by one
 * 
 * EXAMPLE USAGE:
 *      int* binary = toBinary(position);
 * @param int position The value of position is from inputs from users
 * @return int* binary form of the position
 */
int *toBinary(int position);

/**
 * @brief Funtion returns the length of binary array
 * 
 * @return length of binary array, so the it can be used to iterate over the binary array
 *          - Do in-shuffle or out-shuffle depending on the value in the current index
 */
int return_binary_size();

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
void partition(decklist *cards, char **first_half, char **second_half, int deck_size);

/**
 * @brief Function to inshuffle the decklist
 * This function needs to call partition() first to obtain two decklists
 * - Depending on the position (defined by the index) in the decklist,
 * - the top most card in the original decklist should now be the second card in the current deck list
 * - if the index is even, then extracts a card from the second_half 
 * - if the index is odd, then extracts a card from the first_half 
 * 
 * EXAMPLE USAGE: 
 *      inshuffle(cards, deck_size);
 * 
 * @param Decklist* cards - the current decklist containing all cards
 * @param int deck_size - the size of the current decklist
 * 
 * @return void
 */
void inshuffle(decklist *cards, int deck_size);

/**
 * @brief Function to outshuffle the decklist
 * This function has the same EXAMPLE USAGE as above
 * - the top most card in the original decklist is still the top most card
 * - even index: extracts a card from the first_half
 * - odd index: extracts a card from the second_half
 * 
 * EXAMPLE USAGE: similar to inshuffle()
 * @param similar to inshuffle()
 * @return void
 */
void outshuffle(decklist *cards, int deck_size);

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
void print_all(decklist *cards, int in);

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
void shuffle(int *binary, int size, decklist *cards, int deck_size);
