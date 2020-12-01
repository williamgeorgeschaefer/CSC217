// William Schaefer (N00857559@students.ncc.edu)
// CSC 217
// Project 2: "Bookstore Part 1"
// Due November 25, 2020 at 11:59 pm
// project2.c 
//
// This code contains the functions I used from the
// textbook to complete this project.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "booklist.h"
#include "invalidlist.h"
#include "createbook.h"
#include "textbook.h"

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