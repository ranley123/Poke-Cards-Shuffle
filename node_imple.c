/*
 * file: node_imple.c
 * @brief This source file is to implement methods of Decklist and Card
 * - make methods for the linked list
 * @author: 170011474
 * @since: March 11th
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"

/*
 * @brief Funtion to generate a new Decklist struct
 * - Initialise the head and the tail Card (node) to NULL
 * 
 * @return Decklist
 */
decklist *makeDecklist()
{
  decklist *cards = malloc(sizeof(decklist));
  if (!cards)
  {
    printf("Failed to make a decklist");
    abort();
  }
  cards->head = NULL; // initialise the head Card
  cards->tail = NULL; // initialise the tail Card
  return cards;
}

/*
 * @brief Funtion to generate a new Card
 * This funtion uses malloc to allocate memory blocks to Card and its content variable
 * - with the content value passed by function
 * 
 * @param Card* node the new card->next will point to it. It usually is NULL.
 * @param char*h A string that represents the content of the card, for example, "6C"
 * 
 * @return Card
 */
card *addNewNode(card *node, char *value)
{
  card *c = malloc(sizeof(struct inode));
  if (!c)
  {
    abort();
  }
  c->content = malloc(sizeof(strlen(value) + 1));
  if (!(c->content))
  {
    abort();
  } // add extra "1" to reserve space for '\0'
  strcpy(c->content, value);
  c->next = node; // usually NULL is passed by this variable
  return c;
}

/*
 * @brief Funtion to add a new Card into the current Decklist
 * This function adds a returned Card from addNewNode() to the deck
 * - set up the next and pre
 * - if the current list is empty, then set up the tail and the head node
 * 
 * @param Decklist* cards the current deck 
 * @param char* i A string that represents the content of the card
 * 
 * @return void
 */
void addCard(decklist *cards, char *value)
{
  card *newCard = addNewNode(NULL, value);
  if (cards->tail == NULL)
  { // if the current deck is empty, set up head and tail first
    cards->head = newCard;
    cards->tail = newCard;
  }
  else
  {                              // the current deck is not empty
    cards->tail->next = newCard; // append the new Card to the deck
    newCard->pre = cards->tail;
    cards->tail = newCard;
  }
}
