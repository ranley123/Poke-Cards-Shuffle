#include "shuffle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define CLUB "\xE2\x99\xA3"
#define HEART "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
#define SPADE "\xE2\x99\xA0"

void read_line(char *str, int cur_size);
void free_all(decklist *cards);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <arg> \n", argv[0]);
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
        int *binary = NULL;
        int binary_size = 0;
        int temp_size = 0;
        char *input = NULL;
        char *delimiter = " ";
        char *token = NULL;

        scanf("%d", &deck_size);
        if (deck_size == -1)
            exit(0);
        scanf("%d", &position);

        temp_size = deck_size * 5;
        input = malloc(temp_size * sizeof(char));

        read_line(input, temp_size);
        token = strtok(input, delimiter);
        addCard(cards, token);
        while (token != NULL)
        {
            token = strtok(NULL, delimiter);
            if (token != NULL)
            {
                addCard(cards, token);
            }
        }

        binary = toBinary(position);
        binary_size = return_binary_size();
        shuffle(binary, binary_size, cards, deck_size);

        free(binary);
        free_all(cards);
        free(input);
    }

    return 0;
}

void read_line(char *temp, int size)
{
    int c = 0;
    int index = 0;
    c = getchar();

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
            break;

        if (index == size)
        {
            temp = realloc(temp, size + 1);
            size += 1;
        }
        if (c == 'C' || c == 'D' || c == 'H' || c == 'S') // extension part
        {
            temp = realloc(temp, size + 3);
            size += 3;
            switch (c)
            {
            case 'C':
                strcat(temp, CLUB);
                break;
            case 'D':
                strcat(temp, DIAMOND);
                break;
            case 'H':
                strcat(temp, HEART);
                break;
            case 'S':
                strcat(temp, SPADE);
                break;
            default:
                break;
            }
            index += 3;
        }
        else
        {
            temp[index] = c;
            index++;
        }
    }
    temp[index] = '\0';
}

void free_all(decklist *cards)
{
    card *cur = cards->head;
    while (cur != NULL)
    {
        card *tmp = cur;
        cur = cur->next;
        free(tmp->content);
        free(tmp);
    }
    free(cards);
}