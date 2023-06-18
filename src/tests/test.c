#include <check.h>
#include <stdio.h>
#include "../src/main/escalonador.c"

START_TEST(test_submit_process)
{
    submit_process(0, 0, 2, 64, 0, 0, 0);
    ck_assert_int_eq(user_queue_0_size, 1);
    ck_assert_int_eq(user_queue_1_size, 0);

    submit_process(1, 1, 10, 128, 1, 3, 3);
    ck_assert_int_eq(user_queue_0_size, 1);
    ck_assert_int_eq(user_queue_1_size, 1);

    submit_process(2, 1, 6, 512, 2, 4, 1);
    ck_assert_int_eq(user_queue_0_size, 1);
    ck_assert_int_eq(user_queue_1_size, 2);
}
END_TEST

START_TEST(test_scheduler)
{
    user_queue_0_size = 0;
    user_queue_1_size = 0;

    submit_process(0, 0, 2, 64, 0, 0, 0);
    submit_process(1, 1, 10, 128, 1, 3, 3);
    submit_process(2, 1, 6, 512, 2, 4, 1);

    scheduler();

    ck_assert_int_eq(user_queue_0_size, 0);
    ck_assert_int_eq(user_queue_1_size, 0);
}
END_TEST

Suite *escalador_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Escalonador");

    // Casos de teste para a função submit_process
    tc_core = tcase_create("submit_process");
    tcase_add_test(tc_core, test_submit_process);
    suite_add_tcase(s, tc_core);

    // Casos de teste para a função scheduler
    tc_core = tcase_create("scheduler");
    tcase_add_test(tc_core, test_scheduler);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = escalador_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
