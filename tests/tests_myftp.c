/*
** EPITECH PROJECT, 2025
** tests_myftp.c
** File description:
** tests_myftp.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(myftp, test_myftp, .init = redirect_all_std)
{
    cr_assert_eq(42, 42);
}
