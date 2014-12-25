/* An integer literal */
typedef struct node_int_t {
    int val;
} node_int_t;

/* An arithmetic AST node */
typedef struct node_arith_t {
    char *type;
    struct expr *op1;
    struct expr *op2;
} node_arith_t;

/* Basic expression types */
typedef enum Type { INT, ARITH } Type;

/* Expression type for ring */
typedef struct expr {
    Type node_type;
    union {
        node_int_t int_val;
        node_arith_t arith_val;
    } body;
} expr;

/* Constructor for integer literal AST nodes */
node_int_t *make_node_int (int val);
/* Constructor for arithmetic AST node */
node_arith_t *make_node_arith (char *type, expr *op1, expr *op2);
