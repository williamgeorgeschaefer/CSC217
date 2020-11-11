#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct book{
        int numCopies;
        char isbn[11];
        char title[200];
        char last[200];
        char first[200];
        struct book *next;
    };

    struct book *header = 0;
    struct book *trailer = 0;

    void add(struct book *newBook){
        struct book *node = (struct book*)malloc(sizeof(struct book));

        node->numCopies = 1;
        strcpy(node->isbn, newBook->isbn);
        strcpy(node->title, newBook->title);
        strcpy(node->last, newBook->last);
        strcpy(node->first, newBook->first);

        node->next = newBook;
        header = node;
    }