#include "s21_smart_calc.h"

// int main(char *argc, int *argv) {
//   char strin[BUF_SIZE] = "-8 + (-s(7)) * (-(78 / (1.5 * 2 - 3) + (3 - 8)))";
//   if (!check_unary_operators(strin)) {
//     printf("incorret input\n");
//   } else {
//     char strout[BUF_SIZE];
//     to_polish_not(strin, strout);
//     printf("strout = %s\n", strout);
//     long double result = calculating(strout);
//     printf("%.8Lf", result);
//   }
//   return 0;
// }

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("incorrect input\n");
  } else {
    char strout[BUF_SIZE];
    to_polish_not(argv[2], strout);
    // printf("strout = %s\n", strout);
    long double result = calculating(strout);
    printf("%.8Lf", result);
  }

  return 0;
}

long double calculating(char *strout) {
  long double values[BUF_SIZE];
  int top = -1;  // top of value's massive
  int i = 0;
  long double res = 0.;
  char *str = strtok(strout, " ");
  while (str != NULL) {
    if (isdigit(str[0])) {
      // printf("str = %s\n", str);
      // printf("str0 = %c\n", str[0]);
      values[++top] = atof(str);
      // printf("value[cur] = %Lf\n", values[top]);
    } else if (is_operator(str[0])) {
      // printf("str = %s\n", str);
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
            printf("delenie na 0\n");
            exit(1);
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
        case '~':
          values[++top] = arg1;
          values[++top] = -arg2;
          break;
        default:
          break;
      }
    } else if (is_func(str[0])) {
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
            printf("sqrt from negative number\n");
            exit(1);
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
  res = values[top];
  return res;
}