// William Schaefer (N00857559@students.ncc.edu)
// CSC 217
// Project 2: "Bookstore Part 1"
// Due November 25, 2020 at 11:59 pm
// project2.c 
//
// This code reads in lines from standard input representing
// books being shipped to the bookstore.  It creates structures
// containing information on a particular book, and stores them
// in a linked list.  It also accepts and rejects lines based on
// the validity of what is passed in.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "booklist.h"
#include "invalidlist.h"
#include "createbook.h"
#include "textbook.h"

char calcCheck(struct book *myBook);

// I learned how to use command line parameters from the following website:
// http://farside.ph.utexas.edu/teaching/329/lectures/node23.html

int main(int argc, char *argv[]) {

    int invalidLinesActive = 0; //Used to see if the switch to print rejected lines is active
    int authorSortActive = 0; //Used to see if the switch to sort the books by author's last name is active
    char inFileName[200] = "books.txt";
    char outFileName[200] = "output.txt";
    FILE *input;
    FILE *output;

    //Checks to see if either sorting switch is active.  Checks for -r, -a, -ar and -ra in any order.
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-r") == 0){
            invalidLinesActive = 1;
        }
        else if(strcmp(argv[i], "-a") == 0){
            authorSortActive = 1;
        }
        else if(strcmp(argv[i], "-ar") == 0 || strcmp(argv[i], "-ra") == 0){
            invalidLinesActive = 1;
            authorSortActive = 1;
        }
        else if(strcmp(argv[i], "-i") == 0){
            if(argc > i + 1){
                strcpy(inFileName, argv[i + 1]);
                i++;
            }
            else{
                fprintf(stderr, "%s%s%s\n", "Usage: ", argv[0], " [-i inFileName] [-o outFileName]");
                fprintf(stderr, "%s%s%s\n", "OR: ", argv[0], " [-o outFileName] [-i inFileName]");
                return 1;
            }
        }
        else if(strcmp(argv[i], "-o") == 0){
            if(argc > i + 1){
                strcpy(outFileName, argv[i + 1]);
                i++;
            }
            else{
                fprintf(stderr, "%s%s%s\n", "Usage: ", argv[0], " [-i inFileName] [-o outFileName]");
                fprintf(stderr, "%s%s%s\n", "OR: ", argv[0], " [-o outFileName] [-i inFileName]");
                return 4;
            }
        }
        else{
            fprintf(stderr, "%s%s%s\n", "Usage: ", argv[0], " [-i inFileName] [-o outFileName]");
            fprintf(stderr, "%s%s%s\n", "OR: ", argv[0], " [-o outFileName] [-i inFileName]");
            return 3;
        }
    }

    if(strlen(inFileName) > 0){
        input = fopen(inFileName, "r");
    }

    if(strlen(outFileName) > 0){
        output = fopen(outFileName, "w");
    }

    if(input == 0){
        fprintf(stderr, "%s%s%s%s\n", argv[0], ": Input file ", inFileName, " not found");
        return 2;
    }

    if(output == 0){
        fprintf(stderr, "%s%s%s%s\n", argv[0], ": Output file ", outFileName, " failed to open");
        return 5;
    }

    printf("%s\n", inFileName);

    int numLines = 0; //number of lines read in so far

    char line[1000]; //the book currently being read in

    char isbn[11]; //the ISBN of the book currently being read in
    char title[200]; //the title of the book currently being read in
    char last[200]; //the last name of the author of the book currently being read in
    char first[200]; //the first name of the author of the book currently being read in

    struct book myBook; //the book currently being processed
    struct book *booksHeader = 0; //the book at the front of the linked list

    int accept = 0; //number of lines that have been accepted
    int reject = 0; //number of lines that have been rejected

    struct invalidLine invalidLine; //the invalid line to be processed if that is the case
    struct invalidLine *invalidLinesHeader = 0; //the header of the list of invalid lines

    int i = getLineFromFile(input, line, 1000); //integer returned after reading in a line of input
    while(line[0] != '\0'){
        if(isBlank(line)){
            numLines++;
            i = getLineFromFile(input, line, 1000);
            continue;
        }
        int success = populateBook(&myBook, line); //integer variable representing the success
        //or failure of creating a book
        if(success == 1){
            struct book *target = bookSearch(booksHeader, myBook.isbn);
            char myBookCheck = calcCheck(&myBook);
            //Increment number of copies if book is found and the processed book has matching input
            if((target != 0) && (bookCompareTitle(target, &myBook) == 0)){
                target->numCopies++;
                accept++;
            }
            //Reject line if ISBN's match but one of the other fields is different
            else if((target != 0) && (bookCompareTitle(target, &myBook) != 0)){
                reject++;
                invalidLinesHeader = addNewInvalidLine(invalidLinesHeader, line);
            }
            //Reject line if check digits are different
            else if(myBookCheck != myBook.isbn[9]){
                reject++;
                invalidLinesHeader = addNewInvalidLine(invalidLinesHeader, line);
            }
            //If list is empty, set header to the book being processed
            else{
                booksHeader = add(booksHeader, &myBook, authorSortActive);
                accept++;
            }
        }
        //Insert process fails
        else{
            reject++;
            invalidLinesHeader = addNewInvalidLine(invalidLinesHeader, line);     
        }
        
        //Increment the number of lines and update i to read in the next line of input
        numLines++;

        i = getLineFromFile(input, line, 1000);
    }
    //Output
    printf("%d%s\n", numLines, " lines of input were processed.\n");
    printList(booksHeader);
    printf("\n%d%s\n", accept, " lines were accepted.");
    printf("%d%s\n", reject, " lines were rejected.");
    if(invalidLinesActive == 1){
        printf("\n%s\n", "The following lines were rejected:\n");
        printInvalidList(invalidLinesHeader);
        printf("\n");
    }

    writeInventory(booksHeader, output);
    return 0;
}

// Function to calculate the check digit
char calcCheck(struct book *myBook) {
    if(myBook == 0){
        return '\0';
    }
    int s = 0;
    int result = 0;
    char d = '\0';
    // Not enough digits in ISBN
    if(strlen(myBook->isbn) < 9){
        return '\0';
    }
    // Calculate check digit
    for(int i = 0; i < 9; i++) {
        s += (((int) myBook->isbn[i]) - '0') * (10 - i);
    }
    // I called the modular operator twice because if
    // s % 11 == 0, result would be equal to 11 and you
    // can't return a single character.
    result = (11 - (s % 11)) % 11;
    if(result == 10){
        d = 'X';
    }
    else{
        d = result + '0';
    }
    return d;
}