#include <check.h>

#include "smart_calc/s21_smart_calc.h"

START_TEST(calculating_test1) {
  const char *str1 = "1.0+3.0-sin(0)+cos(0)*tan(0)";
  ck_assert_double_eq(calculating(str1), 4);
}
END_TEST

START_TEST(calculating_test2) {
  const char *str1 = "log(100)-(ln(1)+3*3)-sqrt(25)";
  ck_assert_double_eq(calculating(str1), -12);
}
END_TEST

START_TEST(calculating_test3) {
  const char *str1 = "5mod5+(-2)^3";
  ck_assert_double_eq(calculating(str1), 5 % 5 + pow(-2, 3));
}
END_TEST

START_TEST(calculating_test4) {
  const char *str1 = "atan()";
  ck_assert_double_nan(calculating(str1));
}
END_TEST

START_TEST(calculating_test5) {
  const char *str1 = "asin(0)+acos(0)/atan(2)";
  ck_assert_double_eq(calculating(str1), asin(0) + acos(0) / atan(2));
}
END_TEST

START_TEST(calculating_test6) {
  const char *str1 = "sqrt(-25)";
  ck_assert_double_nan(calculating(str1));
}
END_TEST

START_TEST(calculating_test7) {
  const char *str1 = "15/0";
  ck_assert_double_nan(calculating(str1));
}
END_TEST

START_TEST(calculating_test8) {
  const char *str1 = "9+";
  ck_assert_double_nan(calculating(str1));
}
END_TEST

START_TEST(calculating_test9) {
  const char *str1 = "-";
  ck_assert_double_nan(calculating(str1));
}
END_TEST

Suite *calc_suite(void) {
  Suite *s = suite_create("smart_calc_testcase");
  TCase *tc_calculating = tcase_create("Core");

  suite_add_tcase(s, tc_calculating);
  tcase_add_test(tc_calculating, calculating_test1);
  tcase_add_test(tc_calculating, calculating_test2);
  tcase_add_test(tc_calculating, calculating_test3);
  tcase_add_test(tc_calculating, calculating_test4);
  tcase_add_test(tc_calculating, calculating_test5);
  tcase_add_test(tc_calculating, calculating_test6);
  tcase_add_test(tc_calculating, calculating_test7);
  tcase_add_test(tc_calculating, calculating_test8);
  tcase_add_test(tc_calculating, calculating_test9);

  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = calc_suite();
  sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}