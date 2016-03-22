/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * solution.c:  Build a calculator that takes normal calculator input and    *
 *              gives the answer (solution to Intermediate problem #4)       *
 *                                                                           *
 * Author:      946336 (https://www.github.com/946336)                       *
 *                                                                           *
 * Compiling:   gcc -Wall -Wextra -pedantic -std=c99 solution.c -o calc -lm  *
 *                                                                           *
 * Running:     ./calc                                                       *
 *                                                                           *
 * Notes:       - This version does not implement paranthersized operations  *
 *                or logarithms                                              *
 *              - This calculator reads from standard input and terminates   *
 *                on EOF (CTRL+D if not piping or redirecting)               *
 *              - This file is a conglomeration of multiple source files.    *
 *                It's not normally this ugly and convoluted                 *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/****************************************************************************/
/*                                   ast.h                                  */
/****************************************************************************/

#ifndef CALC_AST_H
#define CALC_AST_H 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum TYPE
{
    LITERAL = 0,
    PAREN = 1,
    EXP = 2,
    LOG = 3,
    MOD = 4,
    INT = 5,
    PROD = 6,
    QUOT = 7,
    SUM = 8,
    DIFF = 9
} TYPE;

void print_type(TYPE t);

/****************************************************************************/

static const char operators[] = {'(', ')', '*', '/', '+', '-',
                          '^', '%', '\\'};
__attribute__((unused)) static const char *logOp = "log";

/****************************************************************************/

typedef struct AST_Node *AST_Node;

AST_Node AST_new(TYPE type);
AST_Node AST_copy(AST_Node n);

/* Create AST_Node based on character */
/* All but log are based off of the operator character */
/* log is selected with 'l' */
AST_Node AST_newc(char c);

bool AST_isempty(AST_Node n);

void AST_free(AST_Node *n);

AST_Node AST_setleft(AST_Node n, AST_Node left);
AST_Node AST_setright(AST_Node n, AST_Node right);
AST_Node AST_setnum(AST_Node n, double num);

bool AST_full(AST_Node n);
AST_Node AST_insert(AST_Node root, AST_Node n);

bool AST_leaf(AST_Node n);
bool AST_endoftheline(AST_Node n);
bool AST_wellformed(AST_Node n);

TYPE AST_gettype(AST_Node n);
AST_Node AST_getleft(AST_Node n);
AST_Node AST_getright(AST_Node n);
double AST_getnum(AST_Node n);

void AST_print(AST_Node n);

double AST_evaluate(AST_Node root);

#endif

/****************************************************************************/
/*                                  parse.h                                 */
/****************************************************************************/

#ifndef CALC_PARSE_H
#define CALC_PARSE_H

#include <stdlib.h>
#include <stdio.h>

#include "ast.h"

/* Expanding tabs is controlled by the MY_GETLINE_TABWIDTH define */
/* If MY_GETLINE_TABWIDTH is defined, my_getline() will replace   */
/* \t with however many spaces MY_GETLINE_TABWIDTH evaluates to   */
size_t my_getline(char **buf, size_t *size, FILE *fd);

AST_Node parse(char *expr);

#endif

/****************************************************************************/
/*                                   ast.c                                  */
/****************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include <stdbool.h>
#include <math.h>

#include "ast.h"

/****************************************************************************/

const char ADD = '+';
const char SUBTRACT = '-';
const char MULTIPLY = '*';
const char DIVIDE = '/';
const char MODULUS = '%';
const char INTEGER = '\\';
const char POWER = '^';

/****************************************************************************/

static AST_Node AST_insertliteral(AST_Node walk, AST_Node parent, AST_Node n);
static AST_Node AST_insertoperator(AST_Node walk, AST_Node parent, AST_Node n);

/****************************************************************************/

struct AST_Node {
    TYPE type;
    AST_Node left;
    AST_Node right;
    double num;
};

AST_Node AST_new(TYPE type)
{
    AST_Node node = malloc(sizeof(*node));
    if (node == NULL) {
        perror("AST_new");
        exit(EXIT_FAILURE);
    }

    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->num = 0;

    return node;
}

AST_Node AST_copy(AST_Node n)
{
    if (n == NULL) return NULL;
    AST_Node node = malloc(sizeof(*node));
    if (node == NULL) {
        perror("AST_copy");
        exit(EXIT_FAILURE);
    }
    node->type = n->type;
    node->left = AST_copy(n->left);
    node->right = AST_copy(n->right);
    node->num = n->num;

    return node;
}

AST_Node AST_newc(char c)
{
    AST_Node n = malloc(sizeof(*n));
    if (n == NULL) {
        perror("AST_newc");
        exit(EXIT_FAILURE);
    }

    n->left = NULL;
    n->right = NULL;
    n->num = 0;

    switch (c) {
        case '(':
            n->type = PAREN;
            break;
        case ')':
            fprintf(stderr, "%s\n",
                    "Sorry, this feature has not been implemented. :(");
            exit(EXIT_FAILURE);
            break;
        case '*': 
            n->type = PROD;
            break;
        case '/':
            n->type = QUOT;
            break;
        case '+':
            n->type = SUM;
            break;
        case '-':
            n->type = DIFF;
            break;
        case '^':
            n->type = EXP;
            break;
        case '%':
            n->type = MOD;
            break;
        case '\\':
            n->type = INT;
            break;
        case 'l':
            fprintf(stderr, "%s\n",
                    "Sorry, this feature has not been implemented. :(");
            exit(EXIT_FAILURE);
            break;
        default:
            free(n);
            return NULL;
            break; 
    }
    return n;
}

bool AST_isempty(AST_Node n) {
    return n == NULL;
}

void AST_free(AST_Node *n)
{
    if (*n == NULL) {
        return;
    }

    if ((*n)->left != NULL) AST_free(&(*n)->left);
    if ((*n)->right != NULL) AST_free(&(*n)->right);

    free(*n);
    *n = NULL;
}

AST_Node AST_setleft(AST_Node n, AST_Node left)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_setleft: NULL node");
        exit(EXIT_FAILURE);
    }
    if (n->type == LITERAL) {
        fprintf(stderr, "%s\n", "AST_setleft: LITERAL cannot have "
                                "sub-expressions");
        exit(EXIT_FAILURE);
    }
    n->left = left;
    return n;
}

AST_Node AST_setright(AST_Node n, AST_Node right)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_setleft: NULL node");
        exit(EXIT_FAILURE);
    }
    if (n->type == LITERAL) {
        fprintf(stderr, "%s\n", "AST_setright: LITERAL cannot have "
                                "sub-expressions");
        exit(EXIT_FAILURE);
    }
    if (n->type == PAREN) {
        fprintf(stderr, "%s\n", "AST_setright: PAREN cannot have "
                                "a second sub-expression");
        exit(EXIT_FAILURE);
    }
    n->right = right;
    return n;
}

AST_Node AST_setnum(AST_Node n, double num)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_setleft: NULL node");
        exit(EXIT_FAILURE);
    }
    if (n->type != LITERAL) {
        fprintf(stderr, "%s\n", "AST_setnum: only LITERAL may have a numeric "
                                "value");
        exit(EXIT_FAILURE);
    }
    n->num = num;
    return n;
}

bool AST_full(AST_Node n)
{
    if (n == NULL) {
        return false;
    }

    switch (n->type) {
        case LITERAL:
            return true;
        case PAREN:
            return AST_full(n->left);
        default:
            return AST_full(n->left) && AST_full(n->right);
    }
}

AST_Node AST_insert(AST_Node root, AST_Node n)
{
    if (n->type == LITERAL) {
        if (root == NULL) {
            return n;
        }
        else {
            return AST_insertliteral(root, NULL, n);
        }
    }
    else {
        if (root == NULL) {
            fprintf(stderr, "%s\n", "AST_insert: terrible events have "
                                    "transpired. Flee while you can.");
            exit(EXIT_FAILURE);
        }
        else {
            return AST_insertoperator(root, NULL, n);
        }
    }
     // Compiler dummy 
    return root;
}

AST_Node AST_insertliteral(AST_Node walk, AST_Node parent, AST_Node n)
{
    if (n == NULL) {
        return walk;
    }
    if (n->type != LITERAL) {
        fprintf(stderr, "%s\n", "AST_insertliteral: You lied to me!");
        exit(EXIT_FAILURE);
    }

    (void) parent;
    AST_Node root = walk;

    // walk: node at eol (only insert literals into an incomplete tree, so this
    //       is an operator)
    // parent: walk's parent
    while(!AST_endoftheline(walk)) {
        switch (walk->type) {
            case LITERAL:
                fprintf(stderr, "%s\n", "AST_insertliteral: LITERAL reached "
                                        "while inserting LITERAL.");
                exit(EXIT_FAILURE);
                break;
            case PAREN:
                walk = walk->left;
                break;
            default:
                walk = walk->right;
        }
    }

    if (walk->right != NULL) {
        fprintf(stderr, "%s\n", "AST_insertliteral: attempted to insert "
                                "into complete tree");
        exit(EXIT_FAILURE);
    }
    else {
        walk->right = n;
    }
    return root;
}

AST_Node AST_insertoperator(AST_Node walk, AST_Node parent, AST_Node n)
{
    if (n == NULL) {
        return walk;
    }
    if (n->type == LITERAL) {
        fprintf(stderr, "%s\n", "AST_insertoperator: You lied to me!");
        exit(EXIT_FAILURE);
    }

    AST_Node root = walk;
    bool done = false;

    // If root is a literal, then this is easy
    if (root->type == LITERAL) {
        n->left = root;
        return n;
    }

    // If lower priority than the root, then this is easy
    if (root->type < n->type) {
        if (!AST_wellformed(root)) {
            fprintf(stderr, "%s\n", "AST_insertoperator: cannot operate on "
                                    "another operator!");
            exit(EXIT_FAILURE);
        }
        n->left = root;
        return n;
    }

    // If this is a one operator tree, then this is easy
    if (root->right == NULL) {
        fprintf(stderr, "%s\n", "AST_insertoperator: Cannot operate on "
                                "another operator!");
        exit(EXIT_FAILURE);
    }
    else if (root->right->type == LITERAL) {
        if (root->type > n->type) {
            n->left = root->right;
            root->right = n;
            return root;
        }
        else {
            n->left = root;
            return n;
        }
    }

    // Otherwise, we have work to do.

    // walk: node at eol (since this must be a complete tree, walk will be a
    //       LITERAL)
    // parent: walk's parent (this must be an operator)
    // This loop: ensures walk != NULL
    while (!done && !AST_endoftheline(walk)) {
        // Move on step down now (seeded with root/NULL) as opposed to later
        switch (walk->type) {
            case LITERAL:
                // Hint: This should never happen
                fprintf(stderr, "%s\n", "AST_insertoperator: AAAAAAAAAA");
                exit(EXIT_FAILURE);
            case PAREN:
                parent = walk;
                walk = walk->left;
                break;
            default:
                parent = walk;
                walk = walk->right;
        }

        // lower or equal priority to walk
        if (walk->type <= n->type) {
            // higher or equal priority to parent
            // parent->n->walk
            if (n->type <= parent->type) {
                if (!AST_wellformed(walk)) {
                    fprintf(stderr, "%s\n", "AST_insertoperator: cannot "
                                            "operate on another operator");
                    exit(EXIT_FAILURE);
                }
                n->left = walk;
                parent->right = n;
                done = true;
                continue;
            }
            // n->parent->walk
            else {
                // This should have been handled in earlier iterations
                fprintf(stderr, "%s\n", "AST_insertoperator: ...how?");
                exit(EXIT_FAILURE);
            }
        }
        // higher priority than walk
        else {
            // lower priority than parent
            // walk->n && n->parent && parent->walk (not good)
            if (n->type > parent->type) {
                fprintf(stderr, "%s\n", "AST_insertoperator: You have done "
                                        "the impossible.");
                exit(EXIT_FAILURE);
            }
            // higher or equal priority than parent
            // parent->walk->???->n
            else {
                continue;
            }
        }
    }    

    return root;
}

bool AST_leaf(AST_Node n)
{
    if (n == NULL) {
        return false;
    } else {
        switch (n->type) {
            case LITERAL:
                return true;
            case PAREN:
                if (n->left == NULL) {
                    return true;
                }
                else {
                    return false;
                }
            default:
                if ((n->left == NULL) && (n->right == NULL)) {
                    return true;
                }
                else {
                    return false;
                }
        }
        // Compiler dummy
        return false;
    }
}

bool AST_endoftheline(AST_Node n)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_endoftheline: You've managed to get "
                                "past the end of the line. Congratulations.");
        exit(EXIT_FAILURE);
    }

    switch (n->type) {
        case LITERAL:
            return true;
            break;
        case PAREN:
            return (n->left == NULL);
            break;
        default:
            return (n->right == NULL);
    }
     // Compiler dummy 
    return false;
}

bool AST_wellformed(AST_Node n)
{
    if (n == NULL) return false;
    switch (n->type) {
        case LITERAL:
            return !AST_wellformed(n->left) && !AST_wellformed(n->right);
        case PAREN:
            return AST_wellformed(n->left) && !AST_wellformed(n->right);
        default:
            return AST_wellformed(n->left) && AST_wellformed(n->right);
    }
}

TYPE AST_gettype(AST_Node n)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_gettype: NULL node");
        exit(EXIT_FAILURE);
    }
    return n->type;
}

AST_Node AST_getleft(AST_Node n)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_getleft: NULL node");
        exit(EXIT_FAILURE);
    }
    if (n->type == LITERAL) {
        fprintf(stderr, "%s\n", "AST_getleft: LITERAL does not contain "
                                "sub-expressions");
        exit(EXIT_FAILURE);
    }
    return n->left;
}

AST_Node AST_getright(AST_Node n)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_getright: NULL node");
        exit(EXIT_FAILURE);
    }
    if (n->type == LITERAL) {
        fprintf(stderr, "%s\n", "AST_getright: LITERAL does not contain "
                                "sub-expressions");
        exit(EXIT_FAILURE);
    }
    if (n->type == PAREN) {
        fprintf(stderr, "%s\n", "AST_getright: PAREN contains only one "
                                "sub-expression");
        exit(EXIT_FAILURE);
    }
    return n->right;
}

double AST_getnum(AST_Node n)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_getnum: NULL node");
        exit(EXIT_FAILURE);
    }
    if (n->type != LITERAL) {
        fprintf(stderr, "%s\n", "AST_getnum: only LITERALs contain numbers");
        exit(EXIT_FAILURE);
    }
    return n->num;
}

void AST_print(AST_Node n)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_print: malformed AST");
        exit(EXIT_FAILURE);
    }
    char symbol = '@';
    switch (n->type) {
        case LITERAL:
            fprintf(stdout, "%f", n->num);
            break;
        case SUM:
            symbol = ADD;
            AST_print(n->left);
            fprintf(stdout, " %c ", symbol);
            AST_print(n->right);
            break;
        case DIFF:
            symbol = SUBTRACT;
            AST_print(n->left);
            fprintf(stdout, " %c ", symbol);
            AST_print(n->right);
            break;
        case PROD:
            symbol = MULTIPLY;
            AST_print(n->left);
            fprintf(stdout, " %c ", symbol);
            AST_print(n->right);
            break;
        case QUOT:
            symbol = DIVIDE;
            AST_print(n->left);
            fprintf(stdout, " %c ", symbol);
            AST_print(n->right);
            break;
        case MOD:
            symbol = MODULUS;
            AST_print(n->left);
            fprintf(stdout, " %c ", symbol);
            AST_print(n->right);
            break;
        case INT:
            symbol = INTEGER;
            AST_print(n->left);
            fprintf(stdout, " %c ", symbol);
            AST_print(n->right);
            break;
        case EXP:
            symbol = POWER;
            AST_print(n->left);
            fprintf(stdout, " %c ", symbol);
            AST_print(n->right);
            break;
        case LOG:
            fprintf(stdout, "%s ", "log");
            AST_print(n->left);
            fprintf(stdout, " ");
            AST_print(n->right);
            break;
        case PAREN:
            fprintf(stdout, "(");
            AST_print(n->left);
            fprintf(stdout, ")");
            break;
    }
}

/****************************************************************************/

double AST_evaluate(AST_Node n)
{
     // The empty expression is trivially 0 
    if (n == NULL) {
        return 0;
    }

    double left = AST_evaluate(n->left);
    double right = AST_evaluate(n->right);

    switch (n->type) {
        case LITERAL:
            return AST_getnum(n);
            break;
        case PAREN:
            return left;
            break;
        case EXP:
            return powl(left, right);
            break;
        case LOG:
            return logl(left) / logl(right);
            break;
        case MOD:
            return fmod(left, right);
            break;
        case INT:
            return floor(left / right);
            break;
        case PROD:
            return left * right;
            break;
        case QUOT:
            return left / right;
            break;
        case SUM:
            return left + right;
            break;
        case DIFF:
            return left - right;
            break;
    }
     // Compiler dummy 
    return 0;
}

/****************************************************************************/

void print_type(TYPE t)
{
    char *ts;
    switch (t) {
        case LITERAL:
            ts = "LITERAL";
            break;
        case PAREN:
            ts = "PAREN";
            break;
        case EXP:
            ts = "EXP";
            break;
        case LOG:
            ts = "LOG";
            break;
        case MOD:
            ts = "MOD";
            break;
        case INT:
            ts = "INT";
            break;
        case PROD:
            ts = "PROD";
            break;
        case QUOT:
            ts = "QUOT";
            break;
        case SUM:
            ts = "SUM";
            break;
        case DIFF:
            ts = "DIFF";
            break;
    }
    fprintf(stdout, "%7s", ts);
}

/****************************************************************************/
/*                               calculator.c                               */
/****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "parse.h"

int main()
{
    fprintf(stdout, "Permitted mathematical operations:\n");
    fprintf(stderr, "ADD(+), SUBTRACT(-), MULTIPLY(*), DIVIDE(/), MODULUS(%%), "
                    "INTEGER DIVISION(\\), POWER(^)\n");

    char *expr = NULL;
    size_t size;
    size_t len;

    AST_Node root;

    while(!feof(stdin)) {
        len = my_getline(&expr, &size, stdin);

        if (len == (size_t) -1) {
            continue;
        }

        // Eat newline character
        if (len > 0) expr[len - 1] = '\0';

        root = parse(expr);
        if (!AST_isempty(root)) {
            if (AST_wellformed(root)) {
                fprintf(stdout, "= %f\n", AST_evaluate(root));
            }
            else {
                fprintf(stderr, "%s\n", "main: incomplete expression - "
                                          "skipped");
            }
        }
        AST_free(&root);
    }

    free(expr);
    
    return 0;
}

/****************************************************************************/
/*                                  parse.c                                 */
/****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <string.h>

#include "parse.h"
#include "ast.h"

/****************************************************************************/

static const char NULLCHAR = '\0';

static bool isOp(char c);
static bool isLog(char *exp);

 // char **exp is a pass by reference string 
AST_Node next_item(char **expr);

/****************************************************************************/

AST_Node next_item(char **expr)
{
    if (expr == NULL) {
        return NULL;
    }
    if (*expr == NULL) {
        return NULL;
    }
    char *finger = (*expr);
    AST_Node n = NULL;

    while(isspace(*finger)) {
        ++finger;
    }

    if (isOp(*finger)) {
        n = AST_newc(*finger);
        *expr = finger + 1;
    }
    else if (isLog(finger)) {
        n = AST_newc(*finger);
        *expr = finger + 3;
    }
    else {
        char *cmp = finger;
        double num = strtod(finger, &cmp);

         // Number 
        if (cmp != finger) {
            *expr = cmp;

            n = AST_new(LITERAL);
            n = AST_setnum(n, num);
        }
         // Non number and non operator 
        else if (*finger == '\0') {
            return NULL;
        }
        else {
            fprintf(stderr, "%s: [%s]\n", "next_item: parsing error", finger);
            return NULL;
        }
    }
    return n;
}

AST_Node parse(char *expr)
{
    if (expr == NULL) {
        return NULL;
    }

    AST_Node root = next_item(&expr);
    if (root == NULL) {
        return NULL;
    }

    if (AST_gettype(root) != LITERAL) {
        fprintf(stderr, "%s\n", "parse: expression must begin with a literal");
        exit(EXIT_FAILURE);
    }

    AST_Node n;
    while (*expr != NULLCHAR) {
        n = next_item(&expr);
        if (n == NULL) {
            continue;
        }
        root = AST_insert(root, n);
    }

    return root;
}

/****************************************************************************/

static bool isOp(char c)
{
    for(unsigned i = 0; i < sizeof(operators); ++i) {
        if (c == operators[i]){
            return true;
        }
    }
    return false;
}

static bool isLog(char *expr)
{
    size_t i;

    while(isspace(*expr)) ++expr;

    for(i = 0; i < strlen(logOp); ++i) {
        if (expr[i] != logOp[i]) {
            return false;
        }
    }
    return true;
}

/****************************************************************************/

/* Expanding tabs is controlled by the MY_GETLINE_TABWIDTH define */
/* If MY_GETLINE_TABWIDTH is defined, my_getline() will replace   */
/* \t with however many spaces MY_GETLINE_TABWIDTH evaluates to   */
size_t my_getline(char **buf, size_t *size, FILE *fd)
{
        static const int  INIT_SIZE = 256;
        static const char DELIM1 = '\n';
        static const char DELIM2 = '\r';
        static const char NULLCHAR = '\0';

        if (size == NULL) return (size_t) -1;

        if (*buf == NULL) {
                *buf = malloc(INIT_SIZE * sizeof(**buf));
                if (*buf == NULL) return (size_t) -1;
                *size = INIT_SIZE;
        }

        int c;
        size_t i = 0;

        char peeking;
        do {
                if ((i + 2) >= *size){
                        *buf = realloc(*buf, 2 * (*size) + 1);
                        *size *= 2;
                        if (*buf == NULL) {
                                return (size_t) -1;
                        }
                }

                c = fgetc(fd);
                if ((i + 2) >= *size){
                        *buf = realloc(*buf, 2 * (*size) + 1);
                        *size *= 2;
                        if (*buf == NULL) {
                                return (size_t) -1;
                        }
                }
                /* Lines that are actually blank (no newline at all) are */
                /* reported as invalid. Should only happen in an empty   */
                /* file.                                                 */
                if (c < 0){
                        if (i == 0){
                                *size = -1;
                                return (size_t) -1;
                        }
                        else ++i;
                }
                else {
                        (*buf)[i] = c;
                        /* UNIX line endings:       \n   */
                        /* OSX line endings:        \r   */
                        /* Windows line endings     \r\n */
                        #if defined(MY_GETLINE_TABWIDTH)
                                if ((*buf)[i] == TAB) {
                                        if (*size <=
                                            i + MY_GETLINE_TABWIDTH + 1) {
                                                *buf = realloc(*buf,
                                                              2 * (*size) + 1);
                                                *size *= 2;
                                                if (*buf == NULL)
                                                        return (size_t) -1;
                                        }
                                        #if defined(MY_GETLINE_TABSTOPS)
                                        int dst_to_tabstop =
                                                ((i % MY_GETLINE_TABWIDTH) ? 
                                                (i % MY_GETLINE_TABWIDTH) :
                                                MY_GETLINE_TABWIDTH);
                                        for (size_t q = i;
                                             q < i + dst_to_tabstop;
                                             ++q) {
                                                (*buf)[q] = ' ';
                                        }
                                        i += dst_to_tabstop - 1;
                                        #else
                                        for (size_t q = i;
                                             q < i + MY_GETLINE_TABWIDTH;
                                             ++q) {
                                                (*buf)[q] = ' ';
                                        }
                                        i += MY_GETLINE_TABWIDTH - 1;
                                        #endif
                                }
                        #endif
                        /* UNIX or OS9 */
                        if (((*buf)[i] == DELIM1) || (*buf)[i] == DELIM2) {
                                /* Windows */
                                if ((c == DELIM2) &&
                                        (peeking = fgetc(fd)) != DELIM1)
                                                ungetc(peeking, fd);
                                (*buf)[++i] = NULLCHAR;
                                return i;
                        }
                        ++i;
                }
        } while(c > 0); /* EOF returns a negative value */

        (*buf)[i] = NULLCHAR;
        return i;
}

