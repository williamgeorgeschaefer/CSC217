/* William Schaefer (N00857559@students.ncc.edu)
CSC 217
Project 2: "Bookstore Part 1"
Due November 25, 2020 at 11:59 pm
project2.c 

This code reads in lines from standard input representing
books being shipped to the bookstore.  It creates structures
containing information on a particular book, and stores them
in a linked list.  It also accepts and rejects lines based on
the validity of what is passed in. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "booklist.h"
#include "invalidlist.h"

int findLine(char s[], int lim);
char calcCheck(struct book *myBook);

int main() {
    int numLines = 0; //number of lines read in so far
    char line[1000]; //the book currently being read in
    char isbn[11]; //the ISBN of the book currently being read in
    char title[200]; //the title of the book currently being read in
    char last[200]; //the last name of the author of the book currently being read in
    char first[200]; //the first name of the author of the book currently being read in
    struct book myBook; //the book currently being processed
    struct book *header = 0; //the book at the front of the linked list
    int accept = 0; //number of lines that have been accepted
    int reject = 0; //number of lines that have been rejected
    struct invalidLine invalidLine;
    struct invalidLine *header2 = 0;

    int i = findLine(line, 1000); //integer returned after reading in a line of input
    while(line[0] != '\0'){
        if(line[0] == '\n'){
            numLines++;
            i = findLine(line, 1000);
            continue;
        }
        int index = 0; //the index currently being processed
        int digits = 0; //number of digits in the ISBN of the book being read in.
        while(digits < 10 && line[index] != '\0') {
            if(line[index] != ' ' && line[index] != '-' && line[index] != '\n'){
                isbn[digits] = line[index];
                digits++;
            }
            index++;
        }

        isbn[digits] = '\0';
        int numQuotes = 0; //number of quote characters read in
        int titleIndex = 0; //index currently being processed when reading in the title
        while(numQuotes < 2 && line[index] != '\0'){
            if(numQuotes == 0){
                if(line[index] == '\"'){
                    numQuotes++;
                }
            }
            else{
                if(line[index] == '\"'){
                    numQuotes++;
                }
                else{
                    title[titleIndex++] = line[index];
                }
            }
            index++;
        }
        title[titleIndex] = '\0';
        int lastIndex = 0; //index currently being processed when reading in the author's last name
        while(line[index] != ',' && line[index] != '\0'){
            if(line[index] != ' '){
                last[lastIndex++] = line[index];
            }
            index++;
        }
        last[lastIndex] = '\0';
        int firstIndex = 0; //index currently being processed when reading in the author's first name
        while(line[index] != '\n' && line[index] != '\0'){
            if(line[index] != ',' && line[index] != ' '){
                first[firstIndex++] = line[index];
            }
            index++;
        }
        first[firstIndex] = '\0';
        myBook.numCopies = 1;
        strcpy(myBook.isbn, isbn);
        strcpy(myBook.title, title);
        strcpy(myBook.last, last);
        strcpy(myBook.first, first);

        struct book *target = bookSearch(header, myBook.isbn);
        char myBookCheck = calcCheck(&myBook);
        //Increment number of copies if book is found and the processed book has matching input
        if((target != 0) && (bookCompare(target, &myBook) == 1)){
            target->numCopies++;
            accept++;
        }
        //Reject line if ISBN's match but one of the other fields is different
        else if((target != 0) && (bookCompare(target, &myBook) == 0)){
            reject++;
        }
        //Reject line if check digits are different
        else if(myBookCheck != myBook.isbn[9]){
            reject++;
        }
        //If list is empty, set header to the book being processed
        else{
            header = add(header, &myBook);
            accept++;
        }
        //Increment the number of lines and update i to read in the next line of input
        numLines++;

        i = findLine(line, 1000);
    }
    //Output
    printf("%d%s\n", numLines, " lines of input were processed.\n");
    printList(header);
    printf("\n");
    printf("%d%s\n", accept, " lines were accepted.");
    printf("%d%s\n", reject, " lines were rejected.");
    return 0;
}

//Reference to Get Line Function from textbook
int findLine(char s[], int lim) {
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

//Function to calculate the check digit
char calcCheck(struct book *myBook) {
    if(myBook == 0){
        return '\0';
    }
    int s = 0;
    int result = 0;
    char d = '\0';
    if(strlen(myBook->isbn) < 9){
        return '\0';
    }
    for(int i = 0; i < 9; i++) {
        s += (((int) myBook->isbn[i]) - '0') * (10 - i);
    }
    result = (11 - (s % 11)) % 11;
    if(result == 10){
        d = 'X';
    }
    else{
        d = result + '0';
    }
    return d;
}