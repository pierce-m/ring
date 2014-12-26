/* The root AST node, indicating the start of the program. */
typedef struct root_t {
    struct node_expr_t *block;
    struct root_t *next;
} root_t;

/* Inital program root, initialized before parsing begins. */
root_t *program_start;

/* Placeholder for last node in the linked list formed by program roots.*/
root_t *last_successor;

/* Basic types of arithmetic expression */
typedef enum arith_type { ADD, SUB, MUL, DIV } arith_type;

/* An arithmetic AST node */
typedef struct node_arith_t {
    arith_type type;
    struct node_expr_t *op1;
    struct node_expr_t *op2;
} node_arith_t;

/* Basic expression types */
typedef enum expr_type { INT, ARITH } expr_type;

/* Expression type for ring */
typedef struct node_expr_t {
    expr_type type;
    union body {
        int val;
        node_arith_t *arith_val;
    } body;
} node_expr_t;

/* Initializes the first program root. Called before parsing. */
void initialize_program ();

/* The main interpreter function, belongs to interpreter.c 
 * This function is called to interpret the AST after it has been built. */
int interpret ();

/* Initializes the first program root. Called before parsing. */
void initialize_program ();

/* Adds an expression tree to the current root, and creates a
 * new successor root. */
void add_subtree (node_expr_t *block);

/* Constructor for arithmetic AST node */
node_arith_t *make_node_arith (arith_type, node_expr_t *op1, node_expr_t *op2);

/* Constructor for expression from int literal */
node_expr_t *node_expr_from_int (int val);

/* Constructs expressions with arithmetic nodes */
node_expr_t *node_expr_from_arith (node_arith_t *node);
