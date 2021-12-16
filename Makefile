JerryBoree : JerryBoreeMain.o MultiValueHashTable.o HashTable.o KeyValuePair.o LinkedList.o Jerry.o
	gcc JerryBoreeMain.o MultiValueHashTable.o HashTable.o KeyValuePair.o LinkedList.o Jerry.o -o JerryBoree
	
JerryBoreeMain.o : JerryBoreeMain.c MultiValueHashTable.h HashTable.h Defs.h LinkedList.h KeyValuePair.h Jerry.h
	gcc -c JerryBoreeMain.c 

MultiValueHashTable.o : MultiValueHashTable.c MultiValueHashTable.h HashTable.h Defs.h LinkedList.h KeyValuePair.h
	gcc -c MultiValueHashTable.c

HashTable.o: HashTable.c HashTable.h Defs.h LinkedList.h KeyValuePair.h
	gcc -c HashTable.c

KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c
	
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c

Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c
	






clean:
	rm -f *.o JerryBoree
