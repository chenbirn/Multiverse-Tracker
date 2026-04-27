JerryBoree: HashTable.o Jerry.o JerryBoreeMain.o KeyValuePair.o LinkedList.o MultiValueHashTable.o
	gcc HashTable.o Jerry.o JerryBoreeMain.o KeyValuePair.o LinkedList.o MultiValueHashTable.o -o JerryBoree

HashTable.o: HashTable.c HashTable.h Defs.h KeyValuePair.h LinkedList.h
	gcc -c HashTable.c
Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c
JerryBoreeMain.o: JerryBoreeMain.c Defs.h MultiValueHashTable.h \
 HashTable.h KeyValuePair.h LinkedList.h Jerry.h
	gcc -c JerryBoreeMain.c
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c
LinkedList.o: LinkedList.c LinkedList.h Defs.h KeyValuePair.h
	gcc -c LinkedList.c
MultiValueHashTable.o: MultiValueHashTable.c MultiValueHashTable.h \
 HashTable.h Defs.h KeyValuePair.h LinkedList.h
	gcc -c MultiValueHashTable.c
