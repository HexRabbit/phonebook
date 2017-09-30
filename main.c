#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#ifdef OPT
#define OUT_FILE "opt.txt"
#else
#define OUT_FILE "orig.txt"
#endif

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;
#ifdef OPT
    printf("origin size: %d, optimal size: %d\n",sizeof(entry),sizeof(nameEntry));
#endif

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }
#ifdef OPT
    /* build the hashTable */
    nameEntry **hashTable = InitHashTable();
#else
    /* build the entry */
    entry *pHead, *e;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;
#endif

#ifndef OPT
#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
#endif

    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
#ifdef OPT
        appendHash(line, hashTable);
#else
        e = append(line, e);
#endif
    }

    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);
#ifndef OPT
    e = pHead;
#endif

    /* the givn last name to find */
    char input[][MAX_LAST_NAME_SIZE] = {"zyxel", "tankstopper", "zyzop", "invecked", "muise", "amelu", "qwd23djclw", "kenkeikai"};


#ifndef OPT
#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    for(int i=0; i<sizeof(input)/MAX_LAST_NAME_SIZE; ++i) {
#ifdef OPT
        findNameHash(input[i], hashTable);
#else
        findName(input[i], e);
#endif
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    FILE *output = fopen(OUT_FILE, "a");
    fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);

#ifdef OPT
    for(int i=0; i<TABLE_SIZE; i++) {
        for(nameEntry *j=hashTable[i], *nxt; j != NULL; j = nxt) {
            nxt = j->pNext;
            free(j->pBook);
            free(j);
        }
    }
    free(hashTable);
#else
    for(entry *nxt; pHead != NULL; pHead = nxt) {
        nxt = pHead->pNext;
        free(pHead);
    }
#endif
    return 0;
}
