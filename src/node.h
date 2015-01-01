#include "environment.h"
#include <stdio.h>

/* File descriptor for program output */
FILE *RING_OUT;

/*******************************************
 * PROGRAM START
 *******************************************/

/* Program state, has a list of statements and an environment */
typedef struct program_state_t {
    struct node_statement_t *st_list;
    env_t *env;
} program_state_t;

/* Inital program root, initialized before parsing begins. At each newline in the
 * .ring file, program_start->st_list is updated with a new statement. At the end
 * of parsing, the statements in this list are executed by the interpreter. */
program_state_t *program_start;

/* The most recent statement added to the statement list. This variable
 * elimintates the need to iterate to the end of the statement list each time
 * a statement is added. Initialized with program_start. */
struct node_statement_t *last_added;

/* Adds a statement to the st_list */
void add_statement (struct node_statement_t *s);

/********************************************
 * ARITHMETIC NODES
 ********************************************/

/* Basic types of arithmetic expression */
typedef enum arith_type { ADD, SUB, MUL, DIV } arith_type;

/* An arithmetic AST node. Has a type and two arguments, each of
 * which are expressions. */
typedef struct node_arith_t {
    arith_type type;
    struct node_expr_t *op1;
    struct node_expr_t *op2;
} node_arith_t;

/* Constructor for arithmetic AST node */
node_arith_t *make_node_arith (arith_type, struct node_expr_t *op1, struct node_expr_t *op2);

/*******************************************
 * EXPRESSION NODES
 *******************************************/

/* Basic expression types */
typedef enum expr_type { RING, ARITH } expr_type;

/* An expression AST node. Has a type and a body. The body can be an arithmetic
 * expression (for now) or an integer. Note that integer literals do not have
 * their own AST node type. This is because integer literals are recognized as
 * expressions by the parser. Will this change? Maybe. */
typedef struct node_expr_t {
    expr_type type;
    union {
        ring_t *literal;
        node_arith_t *arith_val;
    } body;
} node_expr_t;

/* Constructor for expression from ring type */
node_expr_t *node_expr_from_ring (ring_t *r);

/* Constructs expressions with arithmetic nodes */
node_expr_t *node_expr_from_arith (node_arith_t *node);

/*******************************************
 * STATEMENT NODES
 *******************************************/

/* Basic statement types. Currently the only statement type is and expression. */
typedef enum statement_type { EXPR, PRINT } statement_type;

/* A statement AST node. Has a type, a body, and a pointer to the next statement
 * in the current lexical scope. Statements are seperated in the source by
 * newlines. */
typedef struct node_statement_t {
    statement_type type;
    union {
        node_expr_t *expr;
    } block;
    struct node_statement_t *next;
} node_statement_t;

/* Constructor for statements from lines containing only expressions */
node_statement_t *node_statement_from_expr (node_expr_t *expr);

/* Constructor for print statements, which print expression values. */
node_statement_t *node_statement_from_print (node_expr_t *expr);

/*******************************************
 * API / HELPER FUNS
 *******************************************/

/* Entry point to program interpreter. */
void interpret ();

/* Initializes the first program root. Called before parsing. */
void initialize_AST ();
