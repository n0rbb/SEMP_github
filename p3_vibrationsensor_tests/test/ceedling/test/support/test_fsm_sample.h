#ifndef _TEST_FSM_SAMPLE_H
#define _TEST_FSM_SAMPLE_H

void test_sample(void* buffer, void* args);
void test_write(void* buffer, void* args);

uint32_t get_tick();
uint32_t get_system_status(uint32_t system_id);

#endif
