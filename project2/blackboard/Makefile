project2: project2.o booklist.o invalidlist.o createbook.o
	gcc -g -o project2 project2.o booklist.o invalidlist.o createbook.o
	
clean: 
	rm project2.o booklist.o invalidlist.o createbook.o project2

project2.o: project2.c booklist.h invalidlist.h createbook.h
	gcc -c -g project2.c

booklist.o: booklist.c booklist.h
	gcc -c -g booklist.c

invalidlist.o: invalidlist.c invalidlist.h
	gcc -c -g invalidlist.c

createbook.o: createbook.c createbook.h
	gcc -c -g createbook.c