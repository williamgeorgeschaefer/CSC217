project2: project2.o booklist.o invalidlist.o
	gcc -o project2 project2.o booklist.o -g
	
project2.o: project2.c booklist.h invalidlist.h
	gcc -c project2.c -g

booklist.o: booklist.c booklist.h
	gcc -c booklist.c -g

invalidlist.o: invalidlist.c invalidlist.h
	gcc -c invalidlist.c -g