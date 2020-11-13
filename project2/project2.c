#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "booklist.h"

int findLine(char s[], int lim);
char calcCheck(struct book *myBook);

int main() {
    int numLines = 0;
    char line[1000];
    char isbn[11];
    char title[200];
    char last[200];
    char first[200];
    struct book myBook;
    struct book *header = 0;
    int accept = 0;
    int reject = 0;

    int i = findLine(line, 1000);
    while(line[0] != '\0'){
        if(line[0] == '\n'){
            i = findLine(line, 1000);
            continue;
        }
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

        struct book *target = bookSearch(header, myBook.isbn);
        char myBookCheck = calcCheck(&myBook);
        char targetBookCheck = calcCheck(target);
        if((target != 0) && (bookCompare(target, &myBook) == 1)){
            target->numCopies++;
            accept++;
        }
        else if((target != 0) && (bookCompare(target, &myBook) == 0)){
            reject++;
        }
        else if((target != 0) && (myBookCheck != targetBookCheck)){
            reject++;
        }
        else{
            header = add(header, &myBook);
            accept++;
        }
        numLines++;

        i = findLine(line, 1000);
    }
    printList(header);
    printf("%d\n", accept);
    printf("%d\n", reject);
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
    int s = 0;
    int result;
    char d;
    for(int i = 10; i >= 2; i--) {
        s += ((int) myBook->isbn[i - 2]) * i;
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