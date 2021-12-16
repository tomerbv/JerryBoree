#include "HashTable.h"

struct hashTable_s{
	LinkedList *array;
	int hashNumber;
	CopyFunction copyKey;
	FreeFunction freeKey;
	PrintFunction printKey;
	CopyFunction copyValue;
	FreeFunction freeValue;
	PrintFunction printValue;
	EqualFunction equalKey;
	FreeFunction freelist;
	PrintFunction printlist;
	TransformIntoNumberFunction transformIntoNumber;
};

hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
	if(hashNumber < 0){
		return NULL;
	}
	hashTable ht = (hashTable) malloc(sizeof(struct hashTable_s));
	if(ht == NULL){
		printf("Memory Problem");
		exit(1);
	}
	ht->array =  (LinkedList*) malloc(hashNumber * sizeof(LinkedList));
	if(ht->array == NULL){
		printf("Memory Problem");
		exit(1);
	}
	for(int i=0; i<hashNumber; i++){
		ht->array[i] = createLinkedList( (CopyFunction) copyKVP, (FreeFunction) destroyKeyValuePair,(EqualFunction) isEqualKvp, (EqualFunction) isEqualKey, (PrintFunction) displayKVP);
		if(ht->array[i] == NULL){
			destroyHashTable(ht);
			return NULL;
		}
	}
	ht->copyKey = copyKey;
	ht->copyValue = copyValue;
	ht->equalKey = equalKey;
	ht->freeKey = freeKey;
	ht->freeValue = freeValue;
	ht->printKey = printKey;
	ht->printValue = printValue;
	ht->freelist = (FreeFunction) destroyList;
	ht->printlist = (PrintFunction) displayList;
	ht->transformIntoNumber = transformIntoNumber;
	ht->hashNumber = hashNumber;
	return ht;
}
status destroyHashTable(hashTable ht){
	if(ht == NULL){
		return failure;
	}
	for(int i=0; i<ht->hashNumber; i++){
		if(ht->freelist(ht->array[i]) == failure){
			return failure;
		}
	}
	free(ht->array);
	free(ht);
	return success;
}

status addToHashTable(hashTable ht, Element key, Element value){
	if(ht == NULL || key == NULL || value == NULL){
		return failure;
	}
	if(lookupInHashTable(ht, key) != NULL){
		return failure;
	}
	int ind = (ht->transformIntoNumber(key) % ht->hashNumber);
	KeyValuePair kvp = createKeyValuePair(key, value, ht->copyKey, ht->copyValue, ht->freeKey, ht->freeValue, ht->equalKey, ht->printKey, ht->printValue);
	if (kvp == NULL){
		return failure;
	}
	if(appendNode(ht->array[ind], kvp) == failure){
		destroyKeyValuePair(kvp);
		return failure;
	}
	return success;
}

Element lookupInHashTable(hashTable ht, Element key){
	if(ht == NULL || key == NULL){
		return NULL;
	}
	int ind = (ht->transformIntoNumber(key) % ht->hashNumber);
	if(getLengthList(ht->array[ind]) == 0){
		return NULL;
	}
	return getValue(searchByKeyInList(ht->array[ind], key));
}


status removeFromHashTable(hashTable ht, Element key){
	if(ht == NULL || key == NULL){
		return failure;
	}
	if(lookupInHashTable(ht, key) == NULL){
		return failure;
	}
	int ind = (ht->transformIntoNumber(key) % ht->hashNumber);
	if(deleteNode(ht->array[ind],searchByKeyInList(ht->array[ind], key)) == failure){
		return failure;
	}
	return success;
}

status displayHashElements(hashTable ht){
	if(ht == NULL){
		return failure;
	}
	for(int i=0; i<ht->hashNumber; i++){
		displayList(ht->array[i]);
	}
	return success;
}
