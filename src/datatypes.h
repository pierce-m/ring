/* A wrapper type for all ring primative types to promote
 * pseudo-polymorphism */

typedef enum ring_native_type { INT } ring_native_type;

typedef struct ring_t {
    ring_native_type type;
    union {
        int int_val;
    } value;
} ring_t;

/* Wraps integer literal int a ring_t of type INT. */
ring_t *ring_int (int val);
