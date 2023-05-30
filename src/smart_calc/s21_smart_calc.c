#include "s21_smart_calc.h"

void to_polish_not(const char *strin, char *strout) {
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

void check_unary_operators(char *strin) {
  for (int i = 0; i < strlen(strin); i++) {
    if ((strin[i] == '-' || strin[i] == '+') &&
        (i == 0 || strin[i - 1] == '(' || is_operator(strin[i - 1]))) {
      if (strin[i] == '-') {
        strin[i] = '~';
      } else {
        strin[i] = ' ';
      }
    }
  }
}

void funcs_parsing(char *strin) {
  char output[BUF_SIZE];
  char *functions[] = {"sin",  "cos", "tan", "acos", "asin",
                       "atan", "log", "ln",  "sqrt"};
  char replacements[] = {SIN, COS, TAN, ACOS, ASIN, ATAN, LOG, LN, SQRT};
  int numFunctions = sizeof(functions) / sizeof(functions[0]);

  for (int i = 0; i < numFunctions; i++) {
    char *match = strstr(strin, functions[i]);
    while (match != NULL) {
      int start = match - strin;  // Начальная позиция найденной подстроки
      int end =
          start + strlen(functions[i]);  // Конечная позиция найденной подстроки

      // Проверка окружающих символов
      if ((start == 0 || !isalpha(strin[start - 1])) &&
          (end == strlen(strin) || !isalpha(strin[end]))) {
        // Окружающие символы не являются буквами, производим замену
        strin[start] = replacements[i];
        memmove(strin + start + 1, strin + end, strlen(strin + end) + 1);
      }

      match = strstr(match + 1, functions[i]);
    }
  }
}
