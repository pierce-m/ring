#include "datatypes.h"
#include "../lib/hashtable.h"

/* An environment defines a lexical scope. It is composed of key-value bindings
 * and a pointer to its parent. The parent of the root environment is NULL */
typedef struct env_t {
    struct env_t *parent;
    hashtable *bindings;
} env_t;

/* Creates a binding for the char *name in e. If one already exists, the previous
 * binding is overwritten */
void env_add_binding (char *name, ring_t *value, env_t *e);

/* Looks in the current environment for the value bound to name. */
ring_t *env_lookup (char *name, env_t *e);

/* Creates a new enviroment to extend e */
env_t *env_extend (env_t *e);
