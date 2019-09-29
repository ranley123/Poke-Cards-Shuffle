#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shuffle.h"
#define DECK_SIZE 52
#define MAX_OUT 8
#define MAX_IN 52

bool isSame(decklist *original, decklist *cards);

void mixshuffle(decklist *cards, int in_shuffle_times, int out_shuffle_times, int deck_size);

int main()
{
    // set up reading and writing pointer and file.
    FILE *fp;
    fp = fopen("poker.txt", "r");
    FILE *fpw;
    fpw = fopen("data.txt", "w");

    int deck_size = DECK_SIZE;
    decklist *cards = makeDecklist();
    decklist *original = makeDecklist(); // the original decklist which is used to compared with the decklist above

    if (fp == NULL)
    {
        printf("Can't open the file");
        exit(0);
    }

    for (int i = 0; i < deck_size; i++) // for every card read from the file, added to two decklists respectively
    {
        char temp[3];
        fscanf(fp, "%s", temp);

        addCard(cards, temp);
        addCard(original, temp);
    }

    int in_counter = 0;  // to record how many in-shuffles in a mix-shuffle
    int out_counter = 0; // to record how many out-shuffles in a mix-shuffle
    int counter = 0;     // to record how many mix-shuffles needed to restore

    // since in-shuffles need 52 times to return, so 53 is equal to 1(mod 52)
    // meanwhile, out-shuffles need 8 times to return
    // to reduce the workload, according to the group theory, we can thus only pick range [0, 51]
    for (int i = 0; i < MAX_IN; i++)
    {
        in_counter = i;
        for (int j = 0; j < MAX_OUT; j++) // same principle as above, pick range [0, 7]
        {
            counter = 0;
            out_counter = j;
            do // do mix-shuffles until the current decklist returns to the original decklist
            {
                counter++;
                mixshuffle(cards, i, j, deck_size);
            } while (!isSame(original, cards));
            if (i == 0 && j == 0)
            { // if both are 0, then the counter now is 1, which has to be substracted by 1
                counter--;
            }
            // for convience to extract data to python, we only put data in it without titles
            fprintf(fpw, "%d %d %d\n", in_counter, out_counter, counter);
        }
    }

    free(cards);
    free(original);

    fclose(fp);
    fclose(fpw);

    return 0;
}

/**
 * @brief Function to compare the original decklist with the current decklist
 * - This function uses while loop to iterate over each node of each list
 * 
 * @param decklist* original - The initial and raw decklist from input
 * @param decklist *cards - The current decklist which is used to do mix-shuffles
 * 
 * @return bool
 */
bool isSame(decklist *original, decklist *cards)
{
    card *ori_cur = original->head;
    card *cards_cur = cards->head;
    while (ori_cur != NULL && cards_cur != NULL) // loop over to compare contents
    {
        if (strcmp(ori_cur->content, cards_cur->content) != 0)
        {
            return false;
        }
        ori_cur = ori_cur->next;
        cards_cur = cards_cur->next;
    }
    return true;
}

/**
 * @brief Function to mix-shuffle cards
 * 
 * @param decklist *cards - the current decklist, which is used to do "experiments"
 * @param int in_shuffle_times - indicates how many times the decklist needs to do in-shuffles
 * @param int out_shuffle_times - indicates how many times the decklist needs to do out-shuffles
 * @param int deck_size - the length of the current decklist
 * 
 * @return void
 */
void mixshuffle(decklist *cards, int in_shuffle_times, int out_shuffle_times, int deck_size)
{
    for (int i = 0; i < in_shuffle_times; i++) // do certain times shuffles
    {
        inshuffle(cards, deck_size);
    }
    for (int i = 0; i < out_shuffle_times; i++)
    {
        outshuffle(cards, deck_size);
    }
}
