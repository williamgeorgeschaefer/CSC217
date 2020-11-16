/* William Schaefer (N00857559@students.ncc.edu)
CSC 217
Project 2: "Bookstore Part 1"
Due November 25, 2020 at 11:59 pm
invalidlist.c 

This code contains functions to add invalid lines to the
linked list containing them, and print the items in the list. */

    struct invalidLine* add(struct invalidLine *header, struct invalidLine *newInvalidLine){
        struct invalidLine *node = (struct invalidLine*)malloc(sizeof(struct invalidLine));

        strcpy(node->line, newInvalidLine->line);

        node->next = header;
        header = node;
        return header;
    }