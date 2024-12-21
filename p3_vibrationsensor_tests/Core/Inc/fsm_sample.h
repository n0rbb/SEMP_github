#ifndef _FSM_SAMPLE_H
#define _FSM_SAMPLE_H

#include "fsm.h"
#include <stdint.h>

/**
  * @brief Function type of sample function with two arguments: buffer to store sampled data and pointer to arguments
  */
typedef void (*sample_func_t)(void* buffer, void* args);

/**
  * @brief Function type of write function with two arguments: buffer with samples and pointer to arguments
  */
typedef void (*write_func_t)(void* buffer, void* args);

/**
 * @brief Type of fsm_sample_new argument struct
 */
typedef struct {
    uint32_t system_id;     /*!< Argument passed to get_system_status function to help the
                                 decision on the system activity */
    uint32_t timeout;       /*!< When system is active, sampling period in ticks */
	sample_func_t sample;   /*!< Function of type @ref sample_func_t called for sampling */
	void* sample_args;      /*!< Pointer to sample function arguments */
	write_func_t write;     /*!< Function of type @ref write_func_t called for writing the samples */
	void* write_args;       /*!< Pointer to write function arguments */
	uint32_t sample_bytes;  /*!< Memory needed to store the samples read */
} fsm_sample_args_t;

/**
 * @brief Function required to obtain current tick from the system (implemented outside this module)
 *
 * @retval Current tick value
 */
uint32_t get_tick();

/**
 * @brief Function required to obtain current status of the system (implemented outside this module)
 * @param system_id : identifier of the polled system, in case there is more than one running
 *
 * @retval Current status: 1 for active (sampling), 0 for inactive (not sampling)
 */
uint32_t get_system_status(uint32_t system_id);

/**
 * @brief Function to create a new fsm_sample instance, allocating and initializing the needed memory
 * @param data : non-NULL pointer to the @ref fsm_sample_args_t struct with custom values for the new fsm_sample created
 *
 * @retval Pointer to the struct storing the fsm_t and the other fields required for fsm_sample
 */
fsm_t* fsm_sample_new(fsm_sample_args_t* data);

/**
 * @brief Function to destroy a fsm_sample instance, to free the allocated memory
 * @param f : pointer to the struct storing fsm_sample data
 *
 */
void fsm_sample_destroy(fsm_t* f);

#endif //_FSM_SAMPLE_H



