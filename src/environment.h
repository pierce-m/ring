#include "datatypes.h"
#include "../lib/hashtable.h"

/* An environment defines a lexical scope. It is composed of key-value bindings
 * and a pointer to its parent. The parent of the root environment is NULL */
typedef struct env {
    struct env *parent;
    hashtable *bindings;
} env;

/* Creates a binding for the char *name in e. If one already exists, the previous
 * binding is overwritten */
void env_add_binding (char *name, ring_type *value, env *e);

/* Looks in the current environment for the value bound to name. */
ring_type *env_lookup (char *name, env *e);

/* Creates a new enviroment to extend e */
env *env_extend (env *e);
