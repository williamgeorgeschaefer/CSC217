project3: project3.o booklist.o invalidlist.o createbook.o textbook.o
	gcc -g -o project3 project3.o booklist.o invalidlist.o createbook.o textbook.o
	
clean: 
	rm project3.o booklist.o invalidlist.o createbook.o textbook.o project3

project3.o: project3.c booklist.h invalidlist.h createbook.h textbook.h
	gcc -c -g project3.c

booklist.o: booklist.c booklist.h
	gcc -c -g booklist.c

invalidlist.o: invalidlist.c invalidlist.h
	gcc -c -g invalidlist.c

createbook.o: createbook.c createbook.h
	gcc -c -g createbook.c

textbook.o: textbook.c textbook.h
	gcc -c -g textbook.c