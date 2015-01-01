#include "environment.h"
#include <stdlib.h>

void
env_add_binding (char *name, ring_type *value, env *e) {
    hash_insert (name, value, e->bindings);
}

//Still needs to handle not-found errors
ring_type*
env_lookup (char *name, env *e) {
    ring_type *val;
    if ((val = hash_get (name, e->bindings)) != NULL) {
        return val;
    } else if (e->parent != NULL) {
        return env_lookup (name, e->parent);
    } else {
        return NULL;
    }
}

env*
env_extend (env *e) {
    env *newEnv = malloc (sizeof (env));
    e->parent = e;
    e->bindings = malloc (sizeof (hashtable));
    return e;
}
