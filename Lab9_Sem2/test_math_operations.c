#include <check.h>
#include <stdlib.h>
#include "math_operations.h"

START_TEST(test_add) {
    ck_assert_float_eq(add(2, 3), 5.0f);
    ck_assert_float_eq(add(1, 1), 2.0f);
}
END_TEST

START_TEST(test_subtract) {
    ck_assert_float_eq(subtract(5, 3), 2.0f);
    ck_assert_float_eq(subtract(3, 5), -2.0f);

}
END_TEST

START_TEST(test_multiply) {
    ck_assert_float_eq(multiply(2, 3), 6.0f);
    ck_assert_float_eq(multiply(1, 5), 5.0f);
}
END_TEST

START_TEST(test_divide) {
    ck_assert_float_eq(divide(6, 3), 2.0f);
    ck_assert_float_eq(divide(1, 2), 0.5f);
    ck_assert_float_eq(divide(5, 0), -1.0f); // Проверка деления на ноль
}
END_TEST


Suite* math_operations_suite(void) {
    Suite* s = suite_create("Math Operations");
    TCase* tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_add);
    tcase_add_test(tc_core, test_subtract);
    tcase_add_test(tc_core, test_multiply);
    tcase_add_test(tc_core, test_divide);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    Suite* s = math_operations_suite();
    SRunner* sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}