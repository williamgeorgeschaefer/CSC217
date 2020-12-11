struct book{
        int numCopies;
        char isbn[11];
        char title[200];
        char last[200];
        char first[200];
        struct book *next;
    };

struct book* add(struct book *header, struct book *newBook, int authorSortActive);
void printList(struct book* header);
struct book* bookSearch(struct book *header, char targetisbn[]);
int bookCompareTitle(struct book *book1, struct book *book2);
int bookCompareLast(struct book *book1, struct book *book2);
void writeInventory(struct book* header, FILE *output);
struct book* delete(struct book* header, struct book* target);