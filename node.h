/*******************************************
 * PROGRAM START
 *******************************************/

/* The root AST node, indicating the start of the program. */
typedef struct root_t {
    struct node_statement_t *st_list;
} root_t;

/* Inital program root, initialized before parsing begins. At each newline in the
 * .ring file, program_start->st_list is updated with a new statement. At the end
 * of parsing, the statements in this list are executed by the interpreter. */
root_t *program_start;

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
typedef enum expr_type { INT, ARITH } expr_type;

/* An expression AST node. Has a type and a body. The body can be an arithmetic
 * expression (for now) or an integer. Note that integer literals do not have
 * their own AST node type. This is because integer literals are recognized as
 * expressions by the parser. Will this change? Maybe. */
typedef struct node_expr_t {
    expr_type type;
    union body {
        int val;
        node_arith_t *arith_val;
    } body;
} node_expr_t;

/* Constructor for expression from int literal */
node_expr_t *node_expr_from_int (int val);

/* Constructs expressions with arithmetic nodes */
node_expr_t *node_expr_from_arith (node_arith_t *node);

/*******************************************
 * STATEMENT NODES
 *******************************************/

/* Basic statement types. Currently the only statement type is and expression. */
typedef enum statement_type { EXPR } statement_type;

/* A statement AST node. Has a type, a body, and a pointer to the next statement
 * in the current lexical scope. Statements are seperated in the source by
 * newlines. */
typedef struct node_statement_t {
    statement_type type;
    union block {
        node_expr_t *expr;
    } block;
    struct node_statement_t *next;
} node_statement_t;

/* Constructor for statements from lines containing only expressions */
node_statement_t *node_statement_from_expr (node_expr_t *expr);

/*******************************************
 * API / HELPER FUNS
 *******************************************/

/* The main interpreter function, belongs to interpreter.c 
 * This function is called to interpret the AST after it has been built. */
int interpret ();

/* Initializes the first program root. Called before parsing. */
void initialize_program ();
