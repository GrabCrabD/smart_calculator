#include "s21_smart_calc.h"

void push(Stack *s, char operation) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->operation = operation;
  node->next = s->top;
  s->top = node;
}

char pop_operator(Stack *s) {
  char operation = s->top->operation;
  Node *temp = s->top;
  s->top = s->top->next;
  free(temp);
  return operation;
}

char peek_operator(Stack *s) { return s->top->operation; }

int is_empty(Stack *s) { return s->top == NULL; }