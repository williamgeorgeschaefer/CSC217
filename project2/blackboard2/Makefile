project2: project2.o booklist.o invalidlist.o createbook.o textbook.o
	gcc -g -o project2 project2.o booklist.o invalidlist.o createbook.o textbook.o
	
clean: 
	rm project2.o booklist.o invalidlist.o createbook.o textbook.o project2

project2.o: project2.c booklist.h invalidlist.h createbook.h textbook.h
	gcc -c -g project2.c

booklist.o: booklist.c booklist.h
	gcc -c -g booklist.c

invalidlist.o: invalidlist.c invalidlist.h
	gcc -c -g invalidlist.c

createbook.o: createbook.c createbook.h
	gcc -c -g createbook.c

textbook.o: textbook.c textbook.h
	gcc -c -g textbook.c