#include "list.h"
#include "src/datatypes.h"

#define MAX_CHAIN_SIZE 7

/* Implementation of a hashtable. Initial size is 10 in anticipation of
 * low number of environment bindings. Collisions are avoided via chaining. */
typedef struct hashtable {
    int size = 10;
    int chain_size = 0;
    struct list *buckets[10];
} hashtable;

typedef struct hash_pair {
    char *key;
    ring_type value;
}

/* Returns a hash of a string based on djb2 -- found here:
 * www.cse.yorku.ca/~oz/hash.html */
unsigned long hash (unsigned char *str);

/* Inserts a key-value pair into hashtable h */
void hash_insert (unsigned char *str, ring_type value, hashtable *h);

/* Retrieves a the value corresponding to key from hashtable h */
ring_type *hash_get (unsigned char *str, hashtable *h);

/* Rehashes the hashtable if the chaining lists grow too large to be
 * efficient */
void rehash (hashtable *h);
