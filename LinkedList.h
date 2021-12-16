#ifndef SRC_LINKEDLIST_H_
#define SRC_LINKEDLIST_H_

#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"

typedef struct t_LinkedList *LinkedList;

LinkedList createLinkedList(CopyFunction copyf, FreeFunction freef, EqualFunction equlf, EqualFunction KeyequlFunc, PrintFunction prntf);
status destroyList(LinkedList lst);
status appendNode(LinkedList lst, Element Node);
status deleteNode(LinkedList lst, Element Node);
status displayList(LinkedList lst);
Element getDatatByIndex(LinkedList lst, int ind);
int getLengthList(LinkedList lst);
Element searchByKeyInList(LinkedList lst, Element key);

Element copyList(LinkedList lst);
LinkedList getList(LinkedList lst);




#endif /* SRC_LINKEDLIST_H_ */
