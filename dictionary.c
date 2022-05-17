
/* The Functions Hash, Check, Load, Unload and Size are implemented
                by me while taking the CS50x22 course
*/

// Implements a dictionary's functionality
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = (word[1] == '\0'
                 || word[1] == '\n') ? 26 * (toupper(word[0]) - 'A') : 26 * (toupper(word[0]) - 'A') + (toupper(word[1]) - 'A');
    node *temp;
    temp = table[index];
    while (temp != NULL)
    {
        char *comparant = malloc(46);
        char *compared = malloc(46);
        strcpy(comparant, temp->word);
        strcpy(compared, word);
        for (int i = 0 ; i < LENGTH + 1 ; i++)
        {
            if (comparant[i] == '\n')
            {
                comparant[i] = '\0';
                break;
            }
        }
        for (int i = 0 ; i < LENGTH + 1 ; i++)
        {
            if (compared[i] == '\n')
            {
                compared[i] = '\0';
                break;
            }
            if (compared[i] == '\0')
            {
                break;
            }
        }
        if (strcasecmp(comparant, compared) == 0)
        {
            free(comparant);
            free(compared);
            return true;
        }
        free(comparant);
        free(compared);
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return word[1] == '\n' ? 26 * (toupper(word[0]) - 'A') : 26 * (toupper(word[0]) - 'A') + (toupper(word[1]) - 'A');
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    printf("Loading...\n");
    FILE *dict = fopen(dictionary, "r");
    node *tmp = NULL;
    if (dict == NULL)
    {
        printf("cant open Dictionary");
        return false;
    }
    char tword[LENGTH + 1];
    while (fgets(tword, 50, dict) != NULL)
    {
        node *p = malloc(sizeof(node));
        p->next = NULL;
        int index = hash(tword);

        //check if table at the calculated index is NULL

        if (table[index] != NULL)
        {
            tmp = table[index];
            // while its NOT NULL go to next node in bucket
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            strcpy(p->word, tword);
            tmp->next = p;
            //printf("%s ---> index : %d\n",tmp->word, index);
        }
        else
        {
            strcpy(p->word, tword);
            table[index] = p;
            //printf("table[%d] = %s\n",index,table[index]->word);
        }
    }
    /* commented code to show all words in a bucket. (for debug ._.)
        */
    printf("\nDictionnary Loaded Successfully\n");
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    for (int i = 0 ; i < 676 ; i++)
    {
        node *tempo;
        tempo = table[i];
        while (tempo != NULL)
        {
            count++;
            tempo = tempo->next;
        }
    }
    //printf("%d",count);
    return count;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *temp;
    for (int i = 0 ; i < 676 ; i++)
    {
        while (table[i] != NULL)
        {
            temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    }
    return true;
}
