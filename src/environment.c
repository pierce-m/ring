#include "environment.h"
#include <stdlib.h>

void
env_add_binding (char *name, ring_t *value, env_t *e) {
    hash_insert (name, value, e->bindings);
}

ring_t*
env_lookup (char *name, env_t *e) {
    ring_t *val;
    if ((val = hash_get (name, e->bindings)) != NULL) {
        return val;
    } else if (e->parent != NULL) {
        return env_lookup (name, e->parent);
    } else {
        return NULL;
    }
}

env_t*
env_extend (env_t *e) {
    env_t *newEnv = malloc (sizeof (env_t));
    e->parent = e;
    e->bindings = malloc (sizeof (hashtable));
    return e;
}
