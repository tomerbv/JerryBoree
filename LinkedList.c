#include "LinkedList.h"


typedef struct Node_t{
	Element value;
	struct Node_t *next;
	struct Node_t *prev;
}Node;

struct t_LinkedList{
	Node *head;
	int size;
	CopyFunction copyFunc;
	FreeFunction freeFunc;
	EqualFunction equlFunc;
	EqualFunction KeyequlFunc;
	PrintFunction prntFunc;
};


Node* initNode(Element value){
	Node* node = (Node*) malloc(sizeof(Node));
	if(node == NULL){
		printf("Memory Problem");
		exit(1);
	}
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return node;
}


LinkedList createLinkedList(CopyFunction copyf, FreeFunction freef, EqualFunction equlf, EqualFunction KeyequlFunc, PrintFunction prntf){
	LinkedList List = (LinkedList) malloc(sizeof(struct t_LinkedList));
	if(List == NULL){
		printf("Memory Problem");
		exit(1);
	}
	List->head = NULL;
	List->size = 0;
	List->copyFunc = copyf;
	List->freeFunc = freef;
	List->equlFunc = equlf;
	List->KeyequlFunc = KeyequlFunc;
	List->prntFunc = prntf;
	return List;
}

status destroyList(LinkedList lst){
	if(lst == NULL){
		return failure;
	}
	while(lst->size > 0){
		if(deleteNode(lst,lst->head->value) == failure){
			return failure;
		}
	}
	free(lst);
	return success;
}

status appendNode(LinkedList lst, Element val){
	if(lst == NULL || val == NULL){
		return failure;
	}
	Node* newNode = initNode(val);
	if(lst->head == NULL){
		lst->head = newNode;
		lst->size += 1;
		return success;
	}
	Node* curr = lst->head;
	while(curr->next != NULL){
		curr = curr->next;
	}
	curr->next = newNode;
	newNode->prev = curr;
	lst->size += 1;
	return success;
}

status deleteNode(LinkedList lst, Element val){
	if(lst == NULL || val == NULL){
		return failure;
	}

	Node* curr = lst->head;
	if (lst->equlFunc(curr->value,val) == true){
		lst->head = curr->next;
		if(lst->head != NULL){
			lst->head->prev = NULL;
		}
		lst->freeFunc(curr->value);
		free(curr);
		lst->size -= 1;
		return success;
	}
	Node* temp = curr->next;
	while(temp != NULL){
		if (lst->equlFunc(temp->value,val) == true){
			curr->next = temp->next;
			if(temp->next != NULL){
				temp->next->prev = curr;
			}
			lst->freeFunc(temp->value);
			free(temp);
			lst->size -= 1;
			return success;
		}
		curr = curr->next;
		temp = temp->next;

	}
	return failure;
}

status displayList(LinkedList lst){
	if(lst == NULL){
		return failure;
	}
	Node* curr = lst->head;
	while (curr != NULL){
		lst->prntFunc(curr->value);
		curr = curr->next;
	}
	return success;
}

Element getDatatByIndex(LinkedList lst, int ind){
	if(lst == NULL || ind > lst->size){
		return NULL;
	}
	Node* curr = lst->head;
	for(int i=1; i<ind;i++){
		curr = curr->next;
	}
	return curr->value;
}

int getLengthList(LinkedList lst){
	return lst->size;
}

Element searchByKeyInList(LinkedList lst, Element key){
	if(lst == NULL || key ==NULL || lst->size == 0){
		return NULL;
	}
	Node* curr = lst->head;
	for(int i=0; i<lst->size; i++){
		if(lst->KeyequlFunc(curr->value,key) == true){
			return curr->value;
		}
		curr = curr->next;
	}
	return NULL;
}

Element copyList(LinkedList lst){
	if(lst == NULL){
		return NULL;
	}
	LinkedList newList = (LinkedList) malloc(sizeof(struct t_LinkedList));
	if(newList == NULL){
		printf("Memory Problem");
		exit(1);
	}
	*newList = *(LinkedList)lst;
	return newList;

}

LinkedList getList(LinkedList lst){
	return lst;
}
