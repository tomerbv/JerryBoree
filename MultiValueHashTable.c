#include "MultiValueHashTable.h"


struct MultiValueHashTable_s{
	hashTable ht;
	CopyFunction copyValue;
	FreeFunction freeValue;
	PrintFunction printValue;
	EqualFunction equalvalue;
	EqualFunction equalvaluekey;
	PrintFunction printKey;
};

MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, EqualFunction equalvalue, EqualFunction equalvaluekey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
	if(hashNumber < 0){
		return NULL;
	}
	MultiValueHashTable mvht = (MultiValueHashTable) malloc(sizeof(struct MultiValueHashTable_s));
	if(mvht == NULL){
		printf("Memory Problem");
		exit(1);
	}
	mvht->ht = createHashTable(copyKey, freeKey, printKey, (CopyFunction) getList, (FreeFunction) destroyList, (PrintFunction) displayList, equalKey, transformIntoNumber, hashNumber);
	if(mvht->ht == NULL){
		return NULL;
	}
	mvht->copyValue = copyValue;        // functions to control the values that are being held
	mvht->equalvalue = equalvalue;
	mvht->equalvaluekey = equalvaluekey;
	mvht->freeValue = freeValue;
	mvht->printValue = printValue;
	mvht->printKey = printKey;
	return mvht;
}


status destroyMultiValueHashTable(MultiValueHashTable mvht){
	if(mvht == NULL){
		return failure;
	}
	if(destroyHashTable(mvht->ht) == failure){
		return failure;
	}
	free(mvht);
	return success;
}


status addToMultiValueHashTable(MultiValueHashTable mvht, Element key, Element value){
	if(mvht == NULL || key == NULL || value == NULL){
		return failure;
	}
	LinkedList existList = (LinkedList) lookupInMultiValueHashTable( mvht,  key);
	if(existList == NULL){
		LinkedList NewList = createLinkedList(mvht->copyValue, mvht->freeValue, mvht->equalvalue, mvht->equalvaluekey, mvht->printValue);
		if(NewList == NULL){
			return failure;
		}
		if(appendNode(NewList, value) == failure){
			destroyList(NewList);
			return failure;
		}
		if(addToHashTable(mvht->ht, key, NewList) == failure){
			destroyList(NewList);
			return failure;
		}
		return success;
	}
	if(appendNode(existList, value) == failure){
		return failure;
	}
	return success;
}


LinkedList lookupInMultiValueHashTable(MultiValueHashTable mvht, Element key){
	if(mvht == NULL || key == NULL){
		return NULL;
	}
	return lookupInHashTable(mvht->ht, key);
}


status removeFromMultiValueHashTable(MultiValueHashTable mvht, Element key, Element value){
	if(mvht == NULL || key == NULL || value == NULL){
		return failure;
	}
	LinkedList existList = (LinkedList) lookupInMultiValueHashTable( mvht,  key);
	if(existList == NULL){
		return failure; // if the key does not exist in the data base
	}
	if(getLengthList(existList) < 2){
		return removeFromHashTable(mvht->ht, key);
	}
	return deleteNode(existList, value);
}


status displayMultiValueHashElementsByKey(MultiValueHashTable mvht, Element key){
	if(mvht == NULL || key == NULL){
		return failure;
	}
	LinkedList existList = (LinkedList) lookupInMultiValueHashTable( mvht,  key);
	if(existList == NULL){
		return failure; // if the key does not exist in the data base
	}
	if(mvht->printKey(key) == failure){
		return failure;
	}
	return displayList(existList);
}

