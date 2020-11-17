// William Schaefer (N00857559@students.ncc.edu)
// CSC 217
// Project 2: "Bookstore Part 1"
// Due November 25, 2020 at 11:59 pm
// booklist.c 
//
// This code contains functions to add books to the
// linked list, print the items in the list, search for books
// and compare two books.  The nodes in the linked list are
// stored alphabetically. 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "booklist.h"
#include "invalidlist.h"

// Add function - Accepts two struct book arguments, the former is
// the head of the list and the latter is the book to be added.  The
// nodes of the linked list are stored alphabetically.
struct book* add(struct book *header, struct book *newBook, int authorSortActive){
    struct book *node = (struct book*)malloc(sizeof(struct book));
    node->numCopies = 1;
    strcpy(node->isbn, newBook->isbn);
    strcpy(node->title, newBook->title);
    strcpy(node->last, newBook->last);
    strcpy(node->first, newBook->first);
    node->next = 0;

    if(header == 0){
        return node;
    }
    if(authorSortActive == 0 && strcmp(header->title, node->title) > 0){
        node->next = header;
        return node;
    }
    else if(authorSortActive != 0 && strcmp(header->last, node->last) > 0){
        node->next = header;
        return node;
    }
    struct book *current = header;
    struct book *previous = header;

    //Alphabetizes the list of books by title
    if(authorSortActive == 0){
        while(current != 0 && strcmp(current->title, node->title) < 0){
            previous = current;
            current = current->next;
        }
    }
    else{
        while(current != 0 && strcmp(current->last, node->last) < 0){
            previous = current;
            current = current->next;
        }
    }
    

    node->next = current;
    previous->next = node;
    return header;
}

// Print List function - Accepts one struct book argument, the header
// of the linked list.  It will print the nodes in order.
void printList(struct book* header) {
    struct book *current = header;
    while(current != 0){
        printf("%s%s%s%s%d%s\n", current->title, " (", current->last, "): ", current->numCopies, " copies");
        current = current->next;
    }
}
/* Book Search function - 
*/
struct book* bookSearch(struct book *header, char targetisbn[]){
    struct book *current = header;
    while(current != 0){
        if(strcmp(current->isbn, targetisbn) == 0){
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