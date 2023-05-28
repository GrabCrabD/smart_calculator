#include "s21_smart_calc.h"

void to_polish_not(char *strin, char *strout) {
  Stack stack;
  stack.top = NULL;

  int i, j = 0;
  for (i = 0; strin[i] != '\0'; i++) {
    if (isdigit(strin[i])) {
      while (isdigit(strin[i]) || strin[i] == '.') {
        strout[j++] = strin[i++];
      }
      strout[j++] = ' ';
      --i;
    } else if (strin[i] == '(' || is_func(strin[i])) {
      push(&stack, strin[i]);
    } else if (strin[i] == ')' || strin[i] == ',') {
      while (!is_empty(&stack) && peek_operator(&stack) != '(') {
        strout[j++] = pop_operator(&stack);
        strout[j++] = ' ';
      }
      if (!is_empty(&stack) && peek_operator(&stack) == '(') {
        pop_operator(&stack);
      }
      if (!is_empty(&stack) && is_func(peek_operator(&stack))) {
        strout[j++] = pop_operator(&stack);
        strout[j++] = ' ';
      }
    } else if (is_operator(strin[i])) {
      while (!is_empty(&stack) && peek_operator(&stack) != '(' &&
             (priority(strin[i]) <= priority(peek_operator(&stack)))) {
        strout[j++] = pop_operator(&stack);
        strout[j++] = ' ';
      }
      push(&stack, strin[i]);
    }
  }

  while (!is_empty(&stack)) {
    strout[j++] = pop_operator(&stack);
    strout[j++] = ' ';
  }

  strout[j] = '\0';
}

int is_func(char func) {
  char *funcs = "sctSCTqlg";
  return strchr(funcs, func) ? SUCCESS : FAILURE;
}

int priority(char op) {
  int pr = FAILURE;
  if (op == '(' || op == ')') {
    pr = 1;
  } else if (op == '+' || op == '-') {
    pr = 2;
  } else if (op == '*' || op == '/' || op == '%') {
    pr = 3;
  } else if (op == '^') {
    pr = 4;
  } else if (op == '~') {
    pr = 5;
  }
  return pr;
}

int is_operator(char op) {
  char *opers = "+-*/^%~";
  return strchr(opers, op) ? SUCCESS : FAILURE;
}

int check_unary_operators(char *strin) {
  int status = FAILURE;
  for (int i = 0; i < strlen(strin); i++) {
    if ((strin[i] == '-' || strin[i] == '+') &&
        (i == 0 || strin[i - 1] == '(' || is_operator(strin[i - 1]))) {
      if (strin[0] == '-') {
        strin[i] = '~';
      } else {
        strin[i] = ' ';
      }
      status = SUCCESS;
    }
  }
  return status;
}
