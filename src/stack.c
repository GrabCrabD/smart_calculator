#include "s21_smart_calc.h"

void push(Stack *s, char operator) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->operator= operator;
  node->next = s->top;
  s->top = node;
}

char pop_operator(Stack *s) {
  char operator= s->top->operator;
  Node *temp = s->top;
  s->top = s->top->next;
  free(temp);
  return operator;
}

char peek_operator(Stack *s) { return s->top->operator; }

int is_empty(Stack *s) { return s->top == NULL; }