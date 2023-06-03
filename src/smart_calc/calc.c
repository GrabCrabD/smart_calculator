#include "s21_smart_calc.h"

double calculating(const char* strin) {
  char strout[BUF_SIZE];
  char copy_strin[BUF_SIZE + 1];
  if (!check_func_arguments(strin)) {
    return NAN;
  }
  strcpy(copy_strin, strin);
  replaceModWithPercent(copy_strin);
  check_unary_operators(copy_strin);
  funcs_parsing(copy_strin);
  to_polish_not(copy_strin, strout);
  double result = get_result(strout);

  return result;
}

double get_result(char* strout) {
  double values[BUF_SIZE];
  int top = -1;  // индекс верхушки массива
  double res = 0.;
  char* str = strtok(strout, " ");
  while (str != NULL) {
    if (isdigit(str[0])) {
      values[++top] = atof(str);
    } else if (is_operator(str[0]) && str[0] != '~') {
      if (top < 1) {
        printf("Insufficient operands\n");
        return NAN;
      }
      double arg2 = values[top--];
      double arg1 = values[top--];
      switch (str[0]) {
        case '+':
          values[++top] = arg1 + arg2;
          break;
        case '-':
          values[++top] = arg1 - arg2;
          break;
        case '/':
          if (arg2 == 0.) {
            printf("division by zero\n");
            return NAN;
          } else {
            values[++top] = arg1 / arg2;
          }
          break;
        case '%':
          values[++top] = fmodl(arg1, arg2);
          break;
        case '*':
          values[++top] = arg1 * arg2;
          break;
        case '^':
          values[++top] = pow(arg1, arg2);
          break;
        default:
          break;
      }
    } else if (str[0] == '~') {
      if (top < 0) {
        printf("Insufficient operands\n");
        return NAN;
      }
      double arg = values[top--];
      values[++top] = -arg;
    } else if (is_func(str[0])) {
      if (top < 0) {
        printf("Insufficient operands\n");
        return NAN;
      }
      double arg = values[top--];
      switch (str[0]) {
        case SIN:
          values[++top] = sinl(arg);
          break;
        case COS:
          values[++top] = cosl(arg);
          break;
        case TAN:
          values[++top] = tanl(arg);
          break;
        case ASIN:
          values[++top] = asinl(arg);
          break;
        case ACOS:
          values[++top] = acosl(arg);
          break;
        case ATAN:
          values[++top] = atanl(arg);
          break;
        case SQRT:
          if (arg < 0) {
            printf("sqrt of a negative value\n");
            return NAN;
          } else {
            values[++top] = sqrt(arg);
          }
          break;
        case LN:
          values[++top] = logl(arg);
          break;
        case LOG:
          values[++top] = log10l(arg);
          break;
        default:
          break;
      }
    }
    str = strtok(NULL, " ");
  }

  if (top != 0) {
    printf("Invalid expression\n");
    return NAN;
  }
  res = values[top];
  return res;
}
