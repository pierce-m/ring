#include "runtime.h"

void
error () {
    fprintf (stderr, "error: %s", ERROR);
}

void
rprintf (ring_t *r) {
    switch (r->type) {
        case INT:
            fprintf (RING_OUT, "%d\n", r->value.int_val);
    }
}
