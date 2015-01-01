#define MAX_CHAIN_SIZE 7

/* Item type for entry in the lists which back hashtable buckets */
typedef struct hash_pair {
    char *key;
    void *val;
    struct hash_pair *next;
} hash_pair;

/* Implementation of a hashtable. Has a size corresponding to number of
 * buckets. */
typedef struct hashtable {
    int size;
    struct hash_pair **buckets;
} hashtable;

/* Returns a hash of a string based on djb2 -- found here:
 * www.cse.yorku.ca/~oz/hash.html */
unsigned long hash (unsigned char *str);

/* Initializes a new hashtable with size buckets */
hashtable *hashtable_init (int size);

/* Frees all memory assiciated with the hash table */
void hashtable_destroy (hashtable *h);

/* Inserts a key-value pair into hashtable h */
void hash_insert (char *str, void *value, hashtable *h);

/* Retrieves a the value corresponding to key from hashtable h. Returns NULL
 * if a key value pair is not found. */
void *hash_get (char *str, hashtable *h);

/* Rehashes the hashtable if the chaining lists grow too large to be
 * efficient */
void rehash (hashtable *h);
