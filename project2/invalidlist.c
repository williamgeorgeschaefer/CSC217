// William Schaefer (N00857559@students.ncc.edu)
// CSC 217
// Project 2: "Bookstore Part 1"
// Due November 25, 2020 at 11:59 pm
// invalidlist.c 

// This code contains functions to add invalid lines to the
// linked list containing them, and print the items in the list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "booklist.h"
#include "invalidlist.h"
#include "createbook.h"

    //List is reversed because new items are placed in the beginning of the list.
    struct invalidLine* addNewInvalidLine(struct invalidLine *header, char newInvalidLine[]){
        struct invalidLine *node = (struct invalidLine*)malloc(sizeof(struct invalidLine));
        //Allocates JUST ENOUGH memory for the invalid line!
        node->line = (char*)malloc((strlen(newInvalidLine)) + 1);

        strcpy(node->line, newInvalidLine);

        node->next = header;
        header = node;
        return header;
    }

    //Recursively reverses the order of the list.
    void printInvalidList(struct invalidLine* header){
        if(header == 0){
            return;
        }
        if(header->next != 0){
            printInvalidList(header->next);
        }
        printf("%s", header->line);
    }