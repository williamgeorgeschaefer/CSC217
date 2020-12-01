struct invalidLine{
        char* line;
        struct invalidLine *next;
    };

struct invalidLine* addNewInvalidLine(struct invalidLine *header, char newInvalidLine[]);
void printInvalidList(struct invalidLine* header);