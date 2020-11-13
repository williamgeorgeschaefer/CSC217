#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "booklist.h"

    struct book* add(struct book *header, struct book *newBook){
        struct book *node = (struct book*)malloc(sizeof(struct book));

        node->numCopies = 1;
        strcpy(node->isbn, newBook->isbn);
        strcpy(node->title, newBook->title);
        strcpy(node->last, newBook->last);
        strcpy(node->first, newBook->first);

        node->next = header;
        header = node;
        return header;
    }

    void printList(struct book* header) {
        struct book *current = header;
        while(current != 0){
            printf("%d\n", current->numCopies);
            printf("%s\n", current->isbn);
            printf("%s\n", current->title);
            printf("%s\n", current->last);
            printf("%s\n", current->first);
            current = current->next;
        }
    }

    struct book* bookSearch(struct book *header, char targetisbn[]){
        struct book *current = header;
        while(current != 0){
            if(strcmp(header->isbn, targetisbn) == 0){
                return current;
            }
            current = current->next;
        }
        return 0;
    }

    int bookCompare(struct book *book1, struct book *book2){
        if((strcmp(book1->title, book2->title) == 0) && (strcmp(book1->last, book2->last) == 0) && (strcmp(book1->first, book2->first) == 0)){
            return 1;
        }
        else{
            return 0;
        }
    }