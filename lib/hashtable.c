#include "hashtable.h"
#include <string.h>
#include <stdlib.h>

unsigned long
hash (unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

hashtable*
hashtable_init (int size) {
    hashtable *h = malloc (sizeof (hashtable));
    h->size = size;
    h->buckets = malloc (sizeof (hash_pair *) * size);
    int i;
    for (i = 0; i < 10; ++i) {
        h->buckets[i] = NULL;
    }
    return h;
}

void hash_chain_destroy (hash_pair *hp) {
    if (hp->next == NULL) {
        free (hp->key);
        free (hp->val);
        free (hp);
    } else {
        hash_chain_destroy (hp->next);
        hash_chain_destroy (hp);
    }
}

void
hashtable_destroy (hashtable *h) {
    int i;
    for (i = 0; i < h->size; ++i)
        hash_chain_destroy (h->buckets[i]);
    free (h->buckets);
    free (h);
}

hash_pair*
hash_pair_init (char *str, void *val) {
    hash_pair *hp = malloc (sizeof (hash_pair));
    hp->key = str;
    hp->val = val;
    hp->next = NULL;
    return hp;
}

hash_pair*
hash_chain_end (hash_pair *hp) {
    for (; hp->next != NULL; hp = hp->next);
    return hp;
}

hash_pair*
hash_pair_get (char *str, hash_pair *hp) {
    for (; hp != NULL; hp = hp->next)
        if (!strcmp(hp->key, str))
            return hp;
    return NULL;
}

void
hash_insert (char *str, void *value, hashtable *h) {
    unsigned long bucket  = hash ((unsigned char *) str) % h->size;
    hash_pair *existing_val;

    if (h->buckets[bucket] == NULL) {
        h->buckets[bucket] = hash_pair_init (str, value);
    } else if ((existing_val = hash_pair_get (str, h->buckets[bucket])) != NULL) {
        existing_val->val = value;
    } else {
        hash_chain_end (h->buckets[hash ((unsigned char*) str) % h->size])->next =
            hash_pair_init (str, value);
    }
}

void*
hash_get (char *str, hashtable *h) {
    hash_pair *hp =
        hash_pair_get (str, h->buckets[hash ((unsigned char*) str) % h->size]);
    return hp == NULL ? NULL : hp->val;
}
