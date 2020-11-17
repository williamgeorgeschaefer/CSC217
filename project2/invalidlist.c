/* William Schaefer (N00857559@students.ncc.edu)
CSC 217
Project 2: "Bookstore Part 1"
Due November 25, 2020 at 11:59 pm
invalidlist.c 

This code contains functions to add invalid lines to the
linked list containing them, and print the items in the list. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "booklist.h"
#include "invalidlist.h"

    struct invalidLine* addNewInvalidLine(struct invalidLine *header, char newInvalidLine[]){
        struct invalidLine *node = (struct invalidLine*)malloc(sizeof(struct invalidLine));

        strcpy(node->line, newInvalidLine);

        node->next = header;
        header = node;
        return header;
    }

    void printInvalidList(struct invalidLine* header){
        printf("%s\n", "The following lines were rejected:\n");
        struct invalidLine* current = header;
        while(current != 0){
            printf("%s\n", current->line);
            current = current->next;
        }
    }