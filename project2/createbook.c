// William Schaefer (N00857559@students.ncc.edu)
// CSC 217
// Project 2: "Bookstore Part 1"
// Due November 25, 2020 at 11:59 pm
// createbook.c
//
// This code reads in lines from standard input representing
// books being shipped to the bookstore.  It creates structures
// containing information on a particular book, and stores them
// in a linked list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "booklist.h"
#include "invalidlist.h"
#include "createbook.h"

// Populate Book function - this function accepts two arguments,
// the former being an empty struct book, the latter being a character
// array to be read in from standard input.  This method returns an
// integer indicating whether or not the book was successfully added
// to the list.
//
// Returns 0 if unsuccessful, 1 if successful.
int populateBook(struct book* newBook, char line[]){

    int index = 0; //the index currently being processed
    int digits = 0; //number of digits in the ISBN of the book being read in.
    while(digits < 10 && line[index] != '\0') {
        if(line[index] != ' ' && line[index] != '-' && line[index] != '\n'){
            newBook->isbn[digits] = line[index];
            digits++;
        }
        index++;
    }
    //ERROR: We have reached the end of the line, having only read in the ISBN.
    if(line[index] == '\0'){
        return 0;
    }
    newBook->isbn[digits] = '\0';
    int numQuotes = 0; //number of quote characters read in
    int titleIndex = 0; //index currently being processed when reading in the title
    while(numQuotes < 2 && line[index] != '\0'){
        if(numQuotes == 0){
            if(line[index] == '\"'){
                numQuotes++;
            }
            //ERROR: We have reached a character that is not a quote or a space.  Reject the line immediately.
            else if(!isspace(line[index])){
                return 0;
            }
        }
        else{
            if(line[index] == '\"'){
                numQuotes++;
            }
            else{
                newBook->title[titleIndex++] = line[index];
            }
        }
        index++;
    }
    //ERROR: We have reached the end of the line because the line does not have an author
    if(line[index] == '\0'){
        return 0;
    }
    newBook->title[titleIndex] = '\0';
    int lastIndex = 0; //index currently being processed when reading in the author's last name
    while(line[index] != ',' && line[index] != '\0'){
        if(line[index] != ' '){
            newBook->last[lastIndex++] = line[index];
        }
        index++;
    }
    //ERROR: We have reached the end of the line because the author has a last name but not a first name
    if(line[index] == '\0'){
        return 0;
    }
    newBook->last[lastIndex] = '\0';
    int firstIndex = 0; //index currently being processed when reading in the author's first name
    while(line[index] != '\n' && line[index] != '\0'){
        if(line[index] != ',' && line[index] != ' '){
            newBook->first[firstIndex++] = line[index];
        }
        index++;
    }
    newBook->first[firstIndex] = '\0';
    newBook->numCopies = 1;
    //SUCCESS: We have reached the end of the line, having read in every parameter in the book structure
    return 1;
}

// Is Blank function - this function accepts one argument, a character array, and sees if it is composed
// entirely of whitespace characters.  If so, it returns a nonzero value.  If not, it returns zero. 
int isBlank(char line[]){
    int i = 0;
    while(line[i] != '\0' && isspace(line[i])){
        i++;
    }
    if(line[i] == '\0'){
        return 1;
    }
    else{
        return 0;
    }
}