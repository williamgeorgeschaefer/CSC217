struct book{
        int numCopies;
        char isbn[11];
        char title[200];
        char last[200];
        char first[200];
        struct book *next;
    };

    struct book *header = 0;
    struct book *trailer = 0;

    void add(struct book newBook){
        
    }