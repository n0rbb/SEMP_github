#include "unity.h"

#define TEST_CASE(...)
#define TEST_RANGE(...)

#include "fsm.h"
#include "fsm_sample.h"
#include "mock_test_fsm_sample.h"

#include <stdlib.h>
#include <string.h>

fsm_t *f;
fsm_sample_args_t args;

#define SAMPLE_ELEMENTS	5

int test_buffer[SAMPLE_ELEMENTS];

/**
 * @file test_fsm_sample.c
 * @author 
 * @author 
 * @brief Tests to develop new generic fsm_sample
 * @version 0.1
 * @date 2024-11-25
 * 
 */


/**
 * @brief Function called before each test to setup the common data: default value in args and 0 in sample buffer
 */
void setUp(void)
{
    args.system_id = 0;
    args.sample = test_sample;
    args.sample_args = NULL;
    args.write = test_write;
    args.write_args = NULL;
    args.timeout = 5;
    args.sample_bytes = SAMPLE_ELEMENTS*sizeof(int);

    memset(test_buffer, 0, sizeof(int)*SAMPLE_ELEMENTS);
}

/**
 * @brief Function called after each test to clean up everything: destroy the allocated memory (if any)
 */
void tearDown(void)
{
	fsm_sample_destroy(f);
}

void stub_sample(void* buffer, void* args, int n) {
	int i;

	//Fake of sample: fill with consecutive values
	int* int_buffer = (int*)buffer;
	for (i=0; i<SAMPLE_ELEMENTS; i++) {
		int_buffer[i] = i+1;
	}
}

void stub_write(void* buffer, void* args, int n) {
	//Fake of write: copy sample buffer content to our test_buffer
	memcpy(test_buffer, buffer, sizeof(int)*SAMPLE_ELEMENTS);
}

/**
 * @brief Comprueba que la funcion de fsm_sample_new devuelve NULL si no tiene argumentos
 *
 */
void test_fsm_sample_new_nullWhenNullArguments(void)
{
    fsm_t *f = (fsm_t*)1;

    get_tick_IgnoreAndReturn(0);
    get_system_status_IgnoreAndReturn(0);

    f = fsm_sample_new(NULL);

    TEST_ASSERT_NULL (f);
}

/**
 * @brief Comprueba que la funcion de fsm_sample_new devuelve NULL si no tiene función sample
 *
 */
void test_fsm_sample_new_nullWhenNullSample(void)
{
    f = (fsm_t*)1;
    args.sample = NULL;

    get_tick_IgnoreAndReturn(0);
    get_system_status_IgnoreAndReturn(0);

    f = fsm_sample_new(&args);

    TEST_ASSERT_NULL (f);
}

/**
 * @brief Comprueba que la funcion de fsm_sample_new devuelve NULL si no tiene función write
 *
 */
void test_fsm_sample_new_nullWhenNullWrite(void)
{
    f = (fsm_t*)1;
    args.write = NULL;

    get_tick_IgnoreAndReturn(0);
    get_system_status_IgnoreAndReturn(0);

    f = fsm_sample_new(&args);

    TEST_ASSERT_NULL (f);
}

/**
 * @brief Comprueba que la funcion de fsm_sample_new devuelve NULL si sample_bytes es 0
 *
 */
void test_fsm_sample_new_nullWhen0SampleBytes(void)
{
    f = (fsm_t*)1;
    args.sample_bytes = 0;

    get_tick_IgnoreAndReturn(0);
    get_system_status_IgnoreAndReturn(0);

    f = fsm_sample_new(&args);

    TEST_ASSERT_NULL (f);
}

/**
 * @brief Dos creaciones dan direcciones distintas
 *
 */
void test_fsm_sample_new_supports_two_instances(void)
{
    fsm_t* f2 = (fsm_t*)1;
	f = (fsm_t*)1;

    f = fsm_sample_new(&args);
    f2 = fsm_sample_new(&args);

    TEST_ASSERT_NOT_EQUAL (f, f2);

    fsm_sample_destroy(f2);

}

/**
 * @brief Comprueba que la funcion de fsm_fire con fsm_sample llama a get_system_status
 *
 */
void test_fsm_sample_fsm_fire_calls_get_system_status_with_correct_argument(void)
{
    args.system_id = 3;
    get_tick_IgnoreAndReturn(0);
    get_system_status_ExpectAndReturn(args.system_id, 1);

    f = fsm_sample_new(&args);

    fsm_fire(f);
}

/**
 * @brief Comprueba que la funcion de fsm_fire con fsm_sample no llama a get_tick si el sistema esta apagado
 *
 */
void test_fsm_sample_fsm_fire_calls_get_tick_not_called_when_system_off(void)
{
    //No get_tick_Ignore to monitor that no call is done to get_tick function
	get_system_status_IgnoreAndReturn(0);

    f = fsm_sample_new(&args);

    fsm_fire(f);
    fsm_fire(f);
    fsm_fire(f);
}

/**
 * @brief Comprueba que la funcion de fsm_fire con fsm_sample llama a get_tick si el sistema esta encendido
 *
 */
void test_fsm_sample_fsm_fire_calls_get_tick_called_when_system_on(void)
{
    get_tick_ExpectAndReturn(0);
    get_system_status_IgnoreAndReturn(1);

    f = fsm_sample_new(&args);

    fsm_fire(f);
}

/**
 * @brief Comprueba que la funcion de fsm_fire con fsm_sample llama test_sample y test_write cuando el tick vale timeout
 *
 */
void test_fsm_sample_fsm_fire_calls_sample_and_write_once_when_system_on_and_timeout_once(void)
{
    get_tick_IgnoreAndReturn(0);
    get_system_status_IgnoreAndReturn(1);

    //Test monitor that these functions are called, no matter which is the argument value used
    test_sample_ExpectAnyArgs();
    test_write_ExpectAnyArgs();

    f = fsm_sample_new(&args);

    fsm_fire(f);

    //Update tick returned to simulate the pass of time
    get_tick_IgnoreAndReturn(args.timeout);
    fsm_fire(f);
    fsm_fire(f);
}

/**
 * @brief Comprueba que la funcion de fsm_fire con fsm_sample llama test_sample y test_write cuando el tick vale timeout con argumentos correctos
 *
 */
void test_fsm_sample_fsm_fire_calls_sample_and_write_with_buffer(void)
{
	int expected_buffer[SAMPLE_ELEMENTS];
	int i;
	for (i=0; i<SAMPLE_ELEMENTS; i++) {
		expected_buffer[i] = i+1;
	}

    get_tick_IgnoreAndReturn(0);
    get_system_status_IgnoreAndReturn(1);

    //Use stubs, more complex function implementation than mock. Fill samples with increasing consecutive values
    test_sample_Stub(stub_sample);
    test_write_Stub(stub_write);

    f = fsm_sample_new(&args);

    fsm_fire(f);

    //Update tick returned to simulate the pass of time
    get_tick_IgnoreAndReturn(args.timeout);
    fsm_fire(f);
    fsm_fire(f);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected_buffer, test_buffer, SAMPLE_ELEMENTS);
}

/**
 * @brief Comprueba que la funcion de fsm_fire con fsm_sample llama test_sample y test_write cuando el tick vale timeout con argumentos correctos
 *
 */
void test_fsm_sample_fsm_fire_calls_sample_and_write_with_args(void)
{
    args.sample_args = (void*)18;
    args.write_args = (void*)25;

    get_tick_IgnoreAndReturn(0);
    get_system_status_IgnoreAndReturn(1);

    //Monitor call to test_sample, forgetting about first argument buffer, checking second argument
    test_sample_Expect(NULL, args.sample_args);
    test_sample_IgnoreArg_buffer();

    //Monitor call to test_write, forgetting about first argument buffer, checking second argument
    test_write_Expect(NULL, args.write_args);
    test_write_IgnoreArg_buffer();

    f = fsm_sample_new(&args);

    fsm_fire(f);

    //Update tick returned to simulate the pass of time
    get_tick_IgnoreAndReturn(args.timeout);
    fsm_fire(f);
    fsm_fire(f);
}

/**
 * @brief Comprueba que la funcion de fsm_fire con fsm_sample llama test_sample y test_write segun tick multiplica timeout
 *
 */
void test_fsm_sample_fsm_fire_calls_sample_and_write_twice_as_tick_increases_to_double_timeout(void)
{
    get_tick_IgnoreAndReturn(0);
    get_system_status_IgnoreAndReturn(1);
    test_sample_ExpectAnyArgs();
    test_write_ExpectAnyArgs();

    f = fsm_sample_new(&args);

    fsm_fire(f);

    //Update tick returned to simulate the pass of time
    get_tick_IgnoreAndReturn(args.timeout);
    fsm_fire(f);

    //No llama test_sample ni test_write
    fsm_fire(f);

    //Update tick returned to simulate the pass of time
    get_tick_IgnoreAndReturn(2*args.timeout);
    test_sample_ExpectAnyArgs();
    test_write_ExpectAnyArgs();

    fsm_fire(f);

}

/**
 * @brief Comprueba que la funcion de fsm_fire con fsm_sample llama test_sample y test_write cuando el tick vale timeout y, al apagar, no se vuelve a llamar
 *
 */
void test_fsm_sample_fsm_fire_no_call_sample_nor_write_when_system_off(void)
{
    get_tick_IgnoreAndReturn(0);
    get_system_status_IgnoreAndReturn(1);
    test_sample_Expect(NULL, args.sample_args);
    test_sample_IgnoreArg_buffer();
    test_write_Expect(NULL, args.write_args);
    test_write_IgnoreArg_buffer();

    f = fsm_sample_new(&args);

    fsm_fire(f);

    //Update tick returned to simulate the pass of time
    get_tick_IgnoreAndReturn(args.timeout);
    fsm_fire(f);

    //No llama test_sample ni test_write
    fsm_fire(f);

    //Update tick returned to simulate the pass of time
    get_tick_IgnoreAndReturn(2*args.timeout);
    get_system_status_IgnoreAndReturn(0);

    //No llama test_sample ni test_write
    fsm_fire(f);

}

/**
 * @brief Dos creaciones pueden funcionar a la vez
 *
 */
void test_fsm_sample_new_supports_two_instances_running(void)
{
    fsm_t* f2 = (fsm_t*)1;
	f = (fsm_t*)1;


    get_tick_IgnoreAndReturn(0);
    get_system_status_IgnoreAndReturn(1);

    //Expect from first
    test_sample_IgnoreArg_buffer();
    test_write_IgnoreArg_buffer();

    f = fsm_sample_new(&args);

    args.timeout = 8;
    args.sample_args = (void*)1;
    args.write_args = (void*)1;
    f2 = fsm_sample_new(&args);

    fsm_fire(f);
    fsm_fire(f2);

    //Update tick returned to simulate the pass of time
    //1x5 ticks
    get_tick_IgnoreAndReturn(5);
    test_sample_Expect(NULL, NULL);
    test_write_ExpectAnyArgs(NULL, NULL);
    fsm_fire(f);

    //1x8 ticks
    get_tick_IgnoreAndReturn(8);
    test_sample_ExpectAnyArgs(NULL, (void*)1);
    test_write_ExpectAnyArgs(NULL, (void*)1);
    fsm_fire(f);

    //2x5 ticks
    get_tick_IgnoreAndReturn(10);
    test_sample_Expect(NULL, NULL);
    test_write_ExpectAnyArgs(NULL, NULL);
    fsm_fire(f);

    //3x5 ticks
    get_tick_IgnoreAndReturn(15);
    test_sample_Expect(NULL, NULL);
    test_write_ExpectAnyArgs(NULL, NULL);
    fsm_fire(f);

    //2x8 ticks
    get_tick_IgnoreAndReturn(16);
    test_sample_ExpectAnyArgs(NULL, (void*)1);
    test_write_ExpectAnyArgs(NULL, (void*)1);
    fsm_fire(f);

    fsm_sample_destroy(f2);

}



