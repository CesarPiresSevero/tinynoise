#include <stdio.h>
#include <stdint.h>
#include <tinynoise.h>
#include <unity.h>

/* First default seed squared (MSB) */
#define FIRST_SAMPLE 65106u

void setUp(void) {}

void tearDown(void) {}

/* Tests tn_run on default conditions */
void test_default_run(void)
{
    int16_t val1 = tn_run();
    /* Check if first value is non-zero */
    TEST_ASSERT_NOT_EQUAL(0,val1);
    /* Check if output matches expected first value */
    TEST_ASSERT_EQUAL(FIRST_SAMPLE,(uint16_t)val1);
    int16_t val2 = tn_run();
    /* Check if output is not repeated */
    TEST_ASSERT_NOT_EQUAL(val1,val2);
}

/* Tests tn_reset function */
void test_reset(void)
{
    int16_t val1 = tn_run();
    /* Check if output is not the first one */
    TEST_ASSERT_NOT_EQUAL(FIRST_SAMPLE,(uint16_t)val1);
    /* Reset lib and check if first value is default */
    tn_reset();
    int16_t val2 = tn_run();
    TEST_ASSERT_EQUAL(FIRST_SAMPLE,(uint16_t)val2);
}

/* Tests tn_set_color function */
void test_set_color(void)
{
    /* Resets lib first */
    tn_reset();
    /* Sets color to white */
    tn_set_color(WHITE);
    /* Check if output matches default */
    int16_t val1 = tn_run();
    TEST_ASSERT_EQUAL(FIRST_SAMPLE,(uint16_t)val1);
    /* Resets lib again */
    tn_reset();
    /* Sets color to brown */
    tn_set_color(BROWN);
    /* Check if output does not matches default */
    int16_t val2 = tn_run();
    TEST_ASSERT_NOT_EQUAL(FIRST_SAMPLE,(uint16_t)val2);
    /* Resets lib again */
    tn_reset();
    /* Sets color to pink */
    tn_set_color(PINK);
    /* Check if output does not matches default */
    int16_t val3 = tn_run();
    TEST_ASSERT_NOT_EQUAL(FIRST_SAMPLE,(uint16_t)val3);
    /* Check if PINK and BROWN are different */
    TEST_ASSERT_NOT_EQUAL(val2,val3);
}

/* Tests tn_set_seed function */
void test_set_seed(void)
{
    /* Resets lib first */
    tn_reset();
    /* Set first seed to zero */
    tn_set_seed(0,DEF_SEED2,DEF_SEED3);
    /* Check if first output is zero */
    int16_t val1 = tn_run();
    TEST_ASSERT_EQUAL(0,val1);
    /* Resets lib */
    tn_reset();
    /* Sets second seed to zero */
    tn_set_seed(DEF_SEED1,0,DEF_SEED3);
    /* Check if second output is equal to first and non-zero */
    val1 = tn_run();
    int16_t val2 = tn_run();
    TEST_ASSERT_EQUAL(val1,val2);
    TEST_ASSERT_NOT_EQUAL(0,val2);
    /* Resets lib */
    tn_reset();
    /* Sets second seed to zero */
    tn_set_seed(DEF_SEED1,DEF_SEED2,0);
    /* Check if third output is equal to second and non-zero */
    val1 = tn_run();
    val2 = tn_run();
    int16_t val3 = tn_run();
    TEST_ASSERT_EQUAL(val2,val3);
    TEST_ASSERT_NOT_EQUAL(0,val3);
}

/* Test runner */
int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_default_run);
    RUN_TEST(test_reset);
    RUN_TEST(test_set_color);
    RUN_TEST(test_set_seed);
    return UNITY_END();
}

