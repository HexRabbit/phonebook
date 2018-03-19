#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define TABLE_SIZE 42737

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT 1
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

typedef struct __NAME_ENTRY {
    entry *pBook;
    struct __NAME_ENTRY *pNext;
} nameEntry;

typedef struct _m_pool {
    char *head;
    char *next;
    unsigned size;
} memPool;

unsigned int djb2(char *str);
entry *findNameHash(char lastName[], nameEntry **hashTable);
void appendHash(char lastName[], nameEntry **hashTable, memPool *mp);
entry *append(char lastName[], entry *e);
nameEntry **InitHashTable();

void pool_init(memPool *mp, unsigned int size);
void *pool_alloc(memPool *mp, unsigned int size);
void pool_free(memPool *mp);

#endif
