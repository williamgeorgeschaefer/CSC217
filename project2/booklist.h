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
struct book* bookSearch(struct book *header, char targetisbn[]);
int bookCompare(struct book *book1, struct book *book2);
int isbnLen(struct book *myBook);