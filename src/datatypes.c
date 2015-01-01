#include <stdlib.h>
#include "datatypes.h"

ring_t*
ring_int (int val) {
    ring_t *r = malloc (sizeof (ring_t));
    r->type = INT;
    r->value.int_val = val;
    return r;
}
