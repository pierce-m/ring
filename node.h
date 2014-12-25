/* An arithmetic AST node */
typedef struct node_arith_t {
    char *type;
    int op1;
    int op2;
} node_arith_t;

/* Constructor for arithmetic AST node */
node_arith_t *make_node_arith(char *, int, int);
