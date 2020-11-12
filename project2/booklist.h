struct book{
        int numCopies;
        char isbn[11];
        char title[200];
        char last[200];
        char first[200];
        struct book *next;
    };

struct book* add(struct book *header, struct book *newBook);
void printList(struct book* header);