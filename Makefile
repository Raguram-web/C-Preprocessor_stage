mypreprocessor : main.o remove_comments.o readFromFIle.o writeToFile.o macro_replacement.o header_inclusion.o
	gcc main.o remove_comments.o readFromFIle.o writeToFile.o macro_replacement.o header_inclusion.o -o mypreprocessor
main.o : main.c header.h
	gcc -c main.c
remove_comments.o : remove_comments.c
	gcc -c remove_comments.c
readFromFIle.o : readFromFIle.c
	gcc -c readFromFIle.c
writeToFile.o : writeToFile.c
	gcc -c writeToFile.c
macro_replacement.o : macro_replacement.c
	gcc -c macro_replacement.c
header_inclusion.o : header_inclusion.c
	gcc -c header_inclusion.c
clean:
	rm -f *.o mypreprocessor a.out
