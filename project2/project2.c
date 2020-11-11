#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "booklist.h"

int findLine(char s[], int lim);

int main() {
    int numLines = 0;
    char line[1000];
    char isbn[11];
    char title[200];
    char last[200];
    char first[200];
    struct book myBook;

    int i = findLine(line, 1000);
    while(line[0] != '\0'){
        int index = 0;
        int digits = 0;
        while(digits < 10 && line[index] != '\0') {
            if(line[index] != ' ' && line[index] != '-' && line[index] != '\n'){
                isbn[digits] = line[index];
                digits++;
            }
            index++;
        }
        isbn[digits] = '\0';
        //printf("%s\n", isbn);
        int numQuotes = 0;
        int titleIndex = 0;
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
        //printf("%s\n", title);
        int lastIndex = 0;
        while(line[index] != ',' && line[index] != '\0'){
            if(line[index] != ' '){
                last[lastIndex++] = line[index];
            }
            index++;
        }
        last[lastIndex] = '\0';
        //printf("%s\n", last);
        int firstIndex = 0;
        while(line[index] != '\n' && line[index] != '\0'){
            if(line[index] != ',' && line[index] != ' '){
                first[firstIndex++] = line[index];
            }
            index++;
        }
        first[firstIndex] = '\0';
        //printf("%s\n", first);
        myBook.numCopies = 1;
        strcpy(myBook.isbn, isbn);
        strcpy(myBook.title, title);
        strcpy(myBook.last, last);
        strcpy(myBook.first, first);

        numLines++;

        i = findLine(line, 1000);
    }
    printf("%d\n", numLines);
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