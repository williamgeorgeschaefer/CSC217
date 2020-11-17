project2: project2.o booklist.o invalidlist.o
	gcc -g -o project2 project2.o booklist.o invalidlist.o
	
clean: 
	rm project2.o booklist.o invalidlist.o project2

project2.o: project2.c booklist.h invalidlist.h
	gcc -c -g project2.c

booklist.o: booklist.c booklist.h
	gcc -c -g booklist.c

invalidlist.o: invalidlist.c invalidlist.h
	gcc -c -g invalidlist.c