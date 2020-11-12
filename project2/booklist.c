#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "booklist.h"

    struct book *header = 0;
    struct book *trailer = 0;

    void add(struct book *newBook){
        struct book *node = (struct book*)malloc(sizeof(struct book));

        node->numCopies = 1;
        strcpy(node->isbn, newBook->isbn);
        strcpy(node->title, newBook->title);
        strcpy(node->last, newBook->last);
        strcpy(node->first, newBook->first);

        node->next = header;
        header = node;
    }

    void printList() {
        struct book *current = header;
        while(current != 0){
            printf("%s\n", current->isbn);
            printf("%s\n", current->title);
            printf("%s\n", current->last);
            printf("%s\n", current->first);
            current = current->next;
        }
    }