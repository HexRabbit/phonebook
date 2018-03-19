#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "phonebook_opt.h"


/* TODO: FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findNameHash(char lastName[], nameEntry **hashTable)
{
    size_t key = djb2(lastName);
    nameEntry *pHead = hashTable[key];
    while(pHead != NULL) {
        if(!strcasecmp(lastName,pHead->pBook->lastName)) {
            return pHead->pBook;
        }
        pHead = pHead->pNext;
    }
    return NULL;
}

void appendHash(char lastName[], nameEntry **hashTable, memPool *mp)
{
    unsigned int key = djb2(lastName);
    nameEntry *ne = (nameEntry *)pool_alloc(mp, sizeof(nameEntry));

    entry *e = (entry *)pool_alloc(mp, sizeof(entry));
    strcpy(e->lastName, lastName);
    ne->pBook = e;
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

void pool_init(memPool *mp, unsigned size)
{
    size = size + (8 - size % 8);
    mp->next = mp->head = malloc(size);
    mp->size = size;
}

void *pool_alloc(memPool *mp, unsigned size)
{
    if(size > mp->size) return NULL;

    mp->size -= size;
    void *tmp = mp->next;
    mp->next += size;
    return tmp;
}

void pool_free(memPool *mp)
{
    free(mp->head);
}
