#ifndef SRC_MULTIVALUEHASHTABLE_H_
#define SRC_MULTIVALUEHASHTABLE_H_
#include"HashTable.h"

typedef struct MultiValueHashTable_s *MultiValueHashTable;

MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, EqualFunction equalvalue, EqualFunction equalvaluekey, TransformIntoNumberFunction transformIntoNumber, int hashNumber);
status destroyMultiValueHashTable(MultiValueHashTable mvht);
status addToMultiValueHashTable(MultiValueHashTable mvht, Element key, Element value);
LinkedList lookupInMultiValueHashTable(MultiValueHashTable mvht, Element key);
status removeFromMultiValueHashTable(MultiValueHashTable mvht, Element key, Element value);
status displayMultiValueHashElementsByKey(MultiValueHashTable mvht, Element key);

#endif /* SRC_MULTIVALUEHASHTABLE_H_ */
