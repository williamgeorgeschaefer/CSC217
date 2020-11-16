struct invalidLine{
        char line[1000];
        struct invalidLine next;
    };

struct invalidLine* add(struct invalidLine *header, struct invalidLine *newInvalidLine);