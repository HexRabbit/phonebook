#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "phonebook_opt.h"


/* TODO: FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findNameHash(char lastName[], nameEntry **hashTable)
{
    size_t key = djb2(lastName);
    nameEntry *pHead = hashTable[key];
    while(pHead != NULL) {
        if(!strcasecmp(lastName,pHead->lastName)) {
            printf("Found name %s !\n", lastName);
            return pHead->pBook;
        }
        pHead = pHead->pNext;
    }
    printf("Name %s not found\n", lastName);
    return NULL;
}

void appendHash(char lastName[], entry *e, nameEntry **hashTable)
{
    unsigned int key = djb2(lastName);
    nameEntry *new = malloc(sizeof(nameEntry));
    strcpy(new->lastName, lastName);
    new->pBook = e;
    new->pNext = hashTable[key];
    hashTable[key] = new;
    return;
}

unsigned int djb2(char *str)
{
    unsigned int hash = TABLE_SIZE;
    int c;

    while(c = *str) {
        hash = ((hash << 5) + hash) + c;
        ++str;
    }
    return hash % TABLE_SIZE;
}

nameEntry **InitHashTable()
{
    unsigned int table_size = TABLE_SIZE;
    nameEntry **pt = malloc(table_size * sizeof(nameEntry *));
    for(int i=0; i<table_size; ++i) {
        pt[i] = NULL;
    }
    return pt;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}
