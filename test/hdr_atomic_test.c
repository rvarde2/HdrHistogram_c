/**
 * hdr_histogram_test.c
 * Written by Michael Barker and released to the public domain,
 * as explained at http://creativecommons.org/publicdomain/zero/1.0/
 */

#include <stdint.h>

#include <stdio.h>
#include <hdr_atomic.h>
#include <rte_eal.h>
#include "minunit.h"

int tests_run = 0;

static char* test_store_load_64(void)
{
    int64_t value = 45;
    int64_t b;
    int64_t p = 0;

    hdr_atomic_store_64(&p, value);
    mu_assert("Failed hdr_atomic_store_64", compare_int64(p, value));

    b = hdr_atomic_load_64(&p);
    mu_assert("Failed hdr_atomic_load_64", compare_int64(p, b));

    return 0;
}

static char* test_store_load_pointer(void)
{
    int64_t r = 12;
    int64_t* q = 0;
    int64_t* s;

    hdr_atomic_store_pointer((void**) &q, &r);
    mu_assert("Failed hdr_atomic_store_pointer", compare_int64(*q, r));

    s = hdr_atomic_load_pointer((void**) &q);
    mu_assert("Failed hdr_atomic_load_pointer", compare_int64(*s, r));

    return 0;
}

static char* test_exchange(void)
{
    int64_t val1 = 123124;
    int64_t val2 = 987234;

    int64_t p = val1;
    int64_t q = val2;
    
    hdr_atomic_exchange_64(&p, q);
    mu_assert("Failed hdr_atomic_exchange_64", compare_int64(p, val2));

    return 0;
}

static char* test_add(void)
{
    int64_t val1 = 123124;
    int64_t val2 = 987234;
    int64_t expected = val1 + val2;

    int64_t result = hdr_atomic_add_fetch_64(&val1, val2);
    mu_assert("Failed hdr_atomic_exchange_64", compare_int64(result, expected));
    mu_assert("Failed hdr_atomic_exchange_64", compare_int64(val1, expected));

    return 0;
}

static struct mu_result all_tests(void)
{
    mu_run_test(test_store_load_64);
    mu_run_test(test_store_load_pointer);
    mu_run_test(test_exchange);
    mu_run_test(test_add);

    mu_ok;
}

static int hdr_atomic_run_tests(void)
{
    struct mu_result result = all_tests();

    if (result.message != 0)
    {
        printf("hdr_atomic_test.%s(): %s\n", result.test, result.message);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result.message == NULL ? 0 : -1;
}

int main(int argc, char **argv)
{
    if (rte_eal_init(argc, argv) < 0) {
            printf("EAL initialization failed\n");
                return 1;
    }
    int testStatus = hdr_atomic_run_tests();
    rte_eal_cleanup();
    return testStatus;
}
