// William Schaefer (N00857559@students.ncc.edu)
// CSC 217
// Project 3: "Bookstore Part 2"
// Due December 21, 2020 at 11:59 am
// project3.c 
//
// This code reads in lines from standard input representing
// books being shipped to the bookstore.  It creates structures
// containing information on a particular book, and stores them
// in a linked list.  It also accepts and rejects lines based on
// the validity of what is passed in.
//
// It then has an interactive portion where the user is the clerk
// of the bookstore.  The user can check to see if an ISBN is in
// the inventory, and the user can also sell copies.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "booklist.h"
#include "invalidlist.h"
#include "createbook.h"
#include "textbook.h"

char calcCheck(char isbn[]);
void getisbn(char line[], char isbn[]);
int populateCommand(char line[], char isbn[]);

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
        // Command to change the input file.
        else if(strcmp(argv[i], "-i") == 0){
            if(argc > i + 1){
                strcpy(inFileName, argv[i + 1]);
                i++;
            }
            // ERROR: User enters -i not followed by a file name.
            else{
                fprintf(stderr, "%s%s%s\n", "Usage: ", argv[0], " [-i inFileName] [-o outFileName]");
                fprintf(stderr, "%s%s%s\n", "OR: ", argv[0], " [-o outFileName] [-i inFileName]");
                return 1;
            }
        }
        // Command to change the output file.
        else if(strcmp(argv[i], "-o") == 0){
            if(argc > i + 1){
                strcpy(outFileName, argv[i + 1]);
                i++;
            }
            // ERROR: User enters -o not followed by a file name.
            else{
                fprintf(stderr, "%s%s%s\n", "Usage: ", argv[0], " [-i inFileName] [-o outFileName]");
                fprintf(stderr, "%s%s%s\n", "OR: ", argv[0], " [-o outFileName] [-i inFileName]");
                return 4;
            }
        }
        // ERROR: User enters invalid input.
        else{
            fprintf(stderr, "%s%s%s\n", "Usage: ", argv[0], " [-i inFileName] [-o outFileName]");
            fprintf(stderr, "%s%s%s\n", "OR: ", argv[0], " [-o outFileName] [-i inFileName]");
            return 3;
        }
    }
    //Open Input File
    if(strlen(inFileName) > 0){
        input = fopen(inFileName, "r");
    }
    //Open Output File
    if(strlen(outFileName) > 0){
        output = fopen(outFileName, "w");
    }

    //ERROR: Input file does not exist.
    if(input == 0){
        fprintf(stderr, "%s%s%s%s\n", argv[0], ": Input file ", inFileName, " not found");
        return 2;
    }

    //ERROR: Input file fails to open.
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
            char myBookCheck = calcCheck(myBook.isbn);
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

    // Start processing interactive commands...
    while(1){
        //Interactive input for the user
        printf("%s", "\nPlease enter a command: ");
        findLine(line, 1000);
        char isbn[11];
        struct book* target;
        struct book* matches[100];
        int numMatches = 0;
        
        //Terminate program if the user enters "q" or "quit"
        if(strcmp(line, "quit\n") == 0 || strcmp(line, "q\n") == 0){
            printf("%s\n", "Process terminating...");
            break;
        }

        // if(strcmp(line, "i\n") == 0){
        //     writeInventory(booksHeader, stdout);
        //     continue;
        // }
        //
        // I temporarily added this invocation to print the current condition of the linked list.
        // I added it for the purpose of debugging the program.
        
        //We are supposed to have a valid ISBN.  We are now testing to see if there is
        //invalid input afterwards.
        int purchaseCopies = populateCommand(line, isbn);
        if(purchaseCopies == -1){
            printf("%s\n", "Invalid input.  Proper use is <ISBN> [<numCopies>].");
            continue;
        }
        
        numMatches = partialSearch(booksHeader, isbn, matches, 100);
        if(numMatches == 0){
            printf("%s\n", "The book you requested is not in the inventory.");
            continue;
        }
        if(purchaseCopies == 0 || numMatches > 1){
            if(numMatches > 1){
                printf("%s\n", "Which of these books did you mean?");
            }
            for(int i = 0; i < numMatches && matches[i] != 0; i++){
                printf("%s%s%s%s%s%s%d%s\n", matches[i]->isbn, " ", matches[i]->title, " (", matches[i]->last, "): ", matches[i]->numCopies, " copies");
            }
            continue;
        }
        else if(numMatches == 1){
            if(purchaseCopies > matches[0]->numCopies){
                printf("%s\n", "Transaction failed.  Not enough copies in inventory.");
                continue;
            }
            matches[0]->numCopies -= purchaseCopies;
            printf("%s%s\n", matches[0]->isbn, " Transaction successful!");
            if(matches[0]->numCopies == 0){
                booksHeader = delete(booksHeader, matches[0]);
            }
        }
    }

    writeInventory(booksHeader, output);
    return 0;
}

// Function to calculate the check digit
char calcCheck(char isbn[]) {
    if(strlen(isbn) == 0){
        return '\0';
    }
    int s = 0;
    int result = 0;
    char d = '\0';
    // Not enough digits in ISBN
    if(strlen(isbn) < 9){
        return '\0';
    }
    // Calculate check digit
    for(int i = 0; i < 9; i++) {
        if(!isdigit(isbn[i])){
            return '\0';
        }
        s += (((int) isbn[i]) - '0') * (10 - i);
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

// Populate Command Function - Accepts two character array arguments, containing the line 
// read in and the ISBN corresponding to the clerk's input.  
// Returns -1 if an error occurs.
// Returns 0 if ISBN is found but a number of copies is not found.
// ISBN character array is populated with the ISBN it read in from the user.
int populateCommand(char line[], char isbn[]){
    if(isBlank(line)){
        return -1;
    }
    int index = 0; //the index currently being processed
    int digits = 0; //number of digits in the ISBN of the book being read in.
    while(digits < 10 && !isspace(line[index]) && line[index] != '\0') {
        if(line[index] != '-' && line[index] != '\n'){
            // The index being processed is not a digit, and it is not the check digit.  Return -1.
            if(digits < 9 && !isdigit(line[index])){
                return -1;
            }
            // The index being processed is the check digit.
            // Return -1 if the check digit is incorrect.
            if(digits == 9){
                if(line[index] != calcCheck(isbn)){
                    return -1;
                }
            }
            isbn[digits] = line[index];
            digits++;
        }
        index++;
    }
    // SET THE LAST INDEX OF ISBN EQUAL TO THE NULL TERMINATOR!!!
    isbn[index] = '\0';
    while(isspace(line[index])){
        index++;
    }
    // We have reached the end of the line, after having only read in the ISBN.
    // The clerk is not checking out any copies.  Return 0.
    if(line[index] == '\0'){
        return 0;
    }
    int numCopies = 0;
    // We are tracking the digits after the whitespace entered by the clerk.
    // This represents the number of the copies.
    while(isdigit(line[index])){
        numCopies = (10 * numCopies) + (line[index] - '0');
        index++;
    }
    // The character(s) that is/are supposed to represent the number of copies
    // contain(s) a character that is not a digit.  Return -1.
    if(!isdigit(line[index]) && !isspace(line[index]) && line[index] != '\0'){
        return -1;
    }
    return numCopies;
}