/**
 * @file: node.h
 * @brief: This header file contains function prototypes from node_imple.c
 * @author: 170011474
 * @since: March 11th
 * 
 */

/**
 * @brief It is used by the card, storing content and next Card, previous Card
 */
typedef struct inode
{
  char *content;
  struct inode *next;
  struct inode *pre;
} card;

/**
 * @brief It is used by the whole deck from the input
 */
typedef struct
{
  card *head, *tail;
} decklist;

/**
 * @brief Funtion to generate a new Decklist struct
 * This function uses malloc to allocate a memory block to Decklist as a linked list
 * - Initialise the head and the tail Card (node) to NULL
 * 
 * EXAMPLE USAGE:
 *    Decklist* cards = makeDecklist(); 
 * @return Decklist
 */
decklist *makeDecklist();

/**
 * @brief Funtion to generate a new Card
 * This funtion uses malloc to allocate memory blocks to Card and its content variable
 * - with the content value passed by function
 * 
 * EXAMPLE USAGE:
 *    Card *card = addNewNode(NULL, i); // i is char* type
 * 
 * @param Card* node the new card->next will point to it. It usually is NULL.
 * @param char*value A string that represents the content of the card, for example, "6C"
 * 
 * @return Card
 */
card *addNewNode(card *node, char *value);

/**
 * @brief Funtion to add a new Card into the current Decklist
 * This function adds a returned Card from addNewNode() to the deck
 * - set up the next and pre
 * - if the current list is empty, then set up the tail and the head node
 * 
 * EXAMPLE USAGE:
 *    Decklist* cards = makeDecklist(); 
 *    char temp[3] = "6C";
 *    addCard(cards, temp);
 * 
 * @param Decklist* cards the current deck 
 * @param char* value A string that represents the content of the card
 * 
 * @return void
 */
void addCard(decklist *q, char *value);
