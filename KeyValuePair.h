#ifndef SRC_KEYVALUEPAIR_H_
#define SRC_KEYVALUEPAIR_H_
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"

typedef struct t_KeyValuePair *KeyValuePair;

KeyValuePair createKeyValuePair(Element key, Element val, CopyFunction keycopyf, CopyFunction valcopyf, FreeFunction keyfreef, FreeFunction valfreef, EqualFunction keyequlf, PrintFunction keyprntf, PrintFunction valprntf);
status destroyKeyValuePair(KeyValuePair kvp);
status displayValue(KeyValuePair kvp);
status displayKey(KeyValuePair kvp);
status displayKVP(KeyValuePair kvp);
Element getValue(KeyValuePair kvp);
Element getKey(KeyValuePair kvp);
KeyValuePair copyKVP(KeyValuePair kvp);
bool isEqualKey(KeyValuePair kvp, Element key);
bool isEqualKvp(KeyValuePair kvp1, KeyValuePair kvp2);


#endif /* SRC_KEYVALUEPAIR_H_ */
