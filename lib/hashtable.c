#include "hashtable.h"

unsigned long
hash (unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

void
hash_insert (unsigned char *str, ring_type value, hashtable *h) {
    list_insert (hash (str) % h->size, value); 
}

ring_type*
hash_get (unsigned char *str, hashtable *h) {
    return list_get (hash (str) % h->size, str);
}
