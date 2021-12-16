#include "KeyValuePair.h"

struct t_KeyValuePair{
	Element value;
	Element key;
	CopyFunction keycopyf;
	CopyFunction valcopyf;
	FreeFunction keyfreef;
	FreeFunction valfreef;
	EqualFunction keyequlf;
	PrintFunction keyprntf;
	PrintFunction valprntf;
};

KeyValuePair createKeyValuePair(Element key, Element val, CopyFunction keycopyf, CopyFunction valcopyf, FreeFunction keyfreef, FreeFunction valfreef, EqualFunction keyequlf, PrintFunction keyprntf, PrintFunction valprntf){
	KeyValuePair kvp = (KeyValuePair) malloc(sizeof(struct t_KeyValuePair));
	if(kvp == NULL){
		printf("Memory Problem");
		exit(1);
	}
	kvp->keycopyf = keycopyf;
	kvp->keyequlf = keyequlf;
	kvp->keyfreef = keyfreef;
	kvp->keyprntf = keyprntf;
	kvp->valcopyf = valcopyf;
	kvp->valfreef = valfreef;
	kvp->valprntf = valprntf;
	kvp->value = kvp->valcopyf(val);
	kvp->key = kvp->keycopyf(key);
	return kvp;
}

KeyValuePair copyKVP(KeyValuePair kvp){
	if(kvp == NULL){
		return NULL;
	}
	KeyValuePair NewKvp = (KeyValuePair) malloc(sizeof(struct t_KeyValuePair));
	if(NewKvp == NULL){
		printf("Memory Problem");
		exit(1);
	}
	*NewKvp = *(KeyValuePair)kvp;
	return NewKvp;

}
status destroyKeyValuePair(KeyValuePair kvp){
	if(kvp == NULL){
		return failure;
	}
	if(kvp->keyfreef(kvp->key) == failure){
		return failure;
	}
	if(kvp->valfreef(kvp->value) == failure){
		return failure;
	}
	free(kvp);
	return success;
}

status displayValue(KeyValuePair kvp){
	if(kvp == NULL){
		return failure;
	}
	if(kvp->valprntf(kvp->value) == failure){
		return failure;
	}
	return success;
}

status displayKey(KeyValuePair kvp){
	if(kvp == NULL){
		return failure;
	}
	if(kvp->keyprntf(kvp->key) == failure){
		return failure;
	}
	return success;
}

status displayKVP(KeyValuePair kvp){
	if(kvp == NULL){
		return failure;
	}
	if(displayKey(kvp) == failure){
		return failure;
	}
	if(displayValue(kvp) == failure){
		return failure;
	}
	return success;
}

Element getValue(KeyValuePair kvp){
	if(kvp == NULL){
		return NULL;
	}
	return kvp->value;
}

Element getKey(KeyValuePair kvp){
	if(kvp == NULL){
		return NULL;
	}
	return kvp->key;
}
bool isEqualKey(KeyValuePair kvp, Element key){
	if(kvp == NULL || key == NULL){
		return false;
	}
	if(kvp->keyequlf(kvp->key,key)){
		return true;
	}
	return false;
}

bool isEqualKvp(KeyValuePair kvp1, KeyValuePair kvp2){
	if(kvp1 == NULL || kvp2 == NULL){
		return false;
	}
	if(kvp1->keyequlf(kvp1->key,kvp2->key)){
		return true;
	}
	return false;
}

