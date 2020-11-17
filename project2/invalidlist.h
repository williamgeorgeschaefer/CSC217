struct invalidLine{
        char line[1000];
        struct invalidLine *next;
    };

struct invalidLine* addNewInvalidLine(struct invalidLine *header, char newInvalidLine[]);
void printInvalidList(struct invalidLine* header);