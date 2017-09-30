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
            return pHead->pBook;
        }
        pHead = pHead->pNext;
    }
    return NULL;
}

void appendHash(char lastName[], nameEntry **hashTable)
{
    unsigned int key = djb2(lastName);
    nameEntry *ne = malloc(sizeof(nameEntry));

    entry *e = malloc(sizeof(entry));
    strcpy(e->lastName, lastName);
    ne->pBook = e;

    strcpy(ne->lastName, lastName);
    ne->pNext = hashTable[key];
    hashTable[key] = ne;
    return;
}

unsigned int djb2(char *str)
{
    unsigned int hash = TABLE_SIZE;
    unsigned int c;

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
