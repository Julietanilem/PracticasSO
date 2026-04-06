#include "scheduler.h"

#ifndef SYSCALLS_H
#define SYSCALLS_H

/**
 * @file syscalls.h
 * @brief Syscall interfaces for GPIO operations.
 */

 /**
 * @brief global semaphores for synchronization between subsystems and radio access.
 */
extern semaphore_t sem_radio;
extern semaphore_t sem_energia;


/**
 * @brief Syscalls interface for gpio write operation.
 * @param pin GPIO pin number
 * @param value 1 for high, 0 for low
 */
void sys_gpio_set(int pin, int value);

/**
 * @brief Syscalls interface for gpio read operation.
 * @param pin GPIO pin number
 * @return 1 if high, 0 if low
 */
int sys_gpio_get(int pin);

/**
 * @brief Syscalls interface for gpio direction configuration.
 * @param pin GPIO pin number
 * @param output 1 for output, 0 for input
 * @return 0 on success, -1 on error (e.g., invalid pin)
 */
int sys_gpio_dir(int pin, int output);


/**
 * @brief Syscalls interface to wait on a semaphore.
 * @param sem Pointer to the semaphore object.
 */
void sys_sem_wait(semaphore_t *sem);

/**
 * @brief Syscalls interface to post a semaphore.
 * @param sem Pointer to the semaphore object.
 */
void sys_sem_post(semaphore_t *sem);

/**
 * @brief Syscalls interface to terminate a task.
 */
void sys_exit(void);

#endif