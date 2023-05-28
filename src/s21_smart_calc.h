#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0
// max buffer size
#define BUF_SIZE 255
// sin(x)
#define SIN 's'
// cos(x)
#define COS 'c'
// tan(x)
#define TAN 't'
// asin(x)
#define ASIN 'S'
// acos(x)
#define ACOS 'C'
// atan(x)
#define ATAN 'T'
// sqrt(x)
#define SQRT 'q'
// ln(x); base e
#define LN 'l'
// log(x); base 10
#define LOG 'g'

/**
 * @brief inside Node
 * @param op operator
 * @param next pointer to the next number
 */
typedef struct Node {
  char operator;
  struct Node *next;
} Node;

/**
 * @brief Stack
 * @param top pointer to the next node in stack
 */
typedef struct {
  Node *top;
} Stack;

void to_polish_not(char *strin, char *strout);
long double calculating(char *strout);

void push(Stack *s, char operator);
char pop_operator(Stack *s);
char peek_operator(Stack *s);
int is_empty(Stack *s);

int is_operator(char op);
int is_func(char func);
int priority(char op);
int check_unary_operators(char *strin);

#endif  // SRC_S21_SMARTCALC_H_