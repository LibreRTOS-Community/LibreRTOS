/*
 * Copyright (C) 2024 LibreRTOS Project
 *
 * This file is part of LibreRTOS.
 *
 * LibreRTOS is free software: you can redistribute it and/or modify
 * it under the terms of the MIT License as published by
 * the Open Source Initiative.
 *
 * LibreRTOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * MIT License for more details.
 *
 * You should have received a copy of the MIT License along with
 * LibreRTOS. If not, see <https://opensource.org/licenses/MIT>.
 */

#ifndef LIBRE_RTOS_PORT_H
#define LIBRE_RTOS_PORT_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Initializes the task stack for a new task.
 *
 * This function sets up the initial stack frame for a new task,
 * ensuring that the task can be properly context-switched when it is scheduled.
 *
 * @param stack_pointer A pointer to the stack pointer of the new task.
 *                      The function will modify this pointer to point to the top of the stack.
 * @param task_func     A pointer to the task function that will be executed by the new task.
 * @param params        A pointer to the task's parameters. This will be passed to the task function.
 *
 * @return None.
 */
void lr_port_kernel_init_task_stack(uint32_t **stack_pointer, void (*task_func)(void), void *params);

/**
 * @brief Starts the scheduler and begins task execution.
 *
 * This function initializes the necessary hardware and software components to start
 * task scheduling. It should be called after all tasks have been created.
 *
 * @return None.
 */
void lr_port_kernel_start_scheduler(void);

/**
 * @brief Saves the current task context.
 *
 * This function saves the context (registers, stack pointer, etc.) of the current task.
 * It is typically called when a context switch is triggered.
 *
 * @param context A pointer to the task's context structure.
 *
 * @return None.
 */
void lr_port_kernel_save_context(void *context);

/**
 * @brief Restores a task context.
 *
 * This function restores the context (registers, stack pointer, etc.) of a task.
 * It is typically called when a task is being resumed.
 *
 * @param context A pointer to the task's context structure.
 *
 * @return None.
 */
void lr_port_kernel_restore_context(void *context);

/**
 * @brief Triggers a context switch to yield the processor to another task.
 *
 * This function initiates a context switch, typically by setting a PendSV interrupt.
 * It can be called by tasks to voluntarily yield the processor.
 *
 * @return None.
 */
void lr_port_kernel_yield(void);

/**
 * @brief Configures the system tick timer.
 *
 * This function sets up the system tick timer to generate periodic interrupts,
 * which are used to implement time slicing in the scheduler.
 *
 * @param tick_rate_hz The frequency of the tick timer, in hertz.
 *
 * @return None.
 */
void lr_port_kernel_setup_tick_timer(uint32_t tick_rate_hz);

/**
 * @brief Handles a system tick.
 *
 * This function should be called by the platform-specific timer interrupt handler
 * (e.g., SysTick on Cortex-M). It updates the system tick count and triggers a
 * context switch if necessary.
 *
 * @return None.
 */
void lr_port_kernel_tick_handler(void);

/**
 * @brief Enters a critical section by disabling interrupts.
 *
 * This function disables interrupts to enter a critical section, ensuring that
 * the code within the section is not interrupted.
 *
 * @return None.
 */
void lr_port_kernel_enter_critical(void);

/**
 * @brief Exits a critical section by enabling interrupts.
 *
 * This function re-enables interrupts, ending a critical section.
 *
 * @return None.
 */
void lr_port_kernel_exit_critical(void);

/**
 * @brief Puts the CPU into low power mode until an interrupt occurs.
 *
 * This function should be called by the idle task to reduce power consumption
 * when the system is idle.
 *
 * @return None.
 */
void lr_port_kernel_enter_low_power(void);

/**
 * @brief Allocates memory dynamically.
 *
 * This function allocates a block of memory of the specified size.
 *
 * @param size The size of the memory block to allocate, in bytes.
 *
 * @return A pointer to the allocated memory block, or NULL if allocation fails.
 */
void *lr_port_kernel_malloc(size_t size);

/**
 * @brief Frees dynamically allocated memory.
 *
 * This function frees a block of memory that was previously allocated with lr_port_kernel_malloc.
 *
 * @param ptr A pointer to the memory block to be freed.
 *
 * @return None.
 */
void lr_port_kernel_free(void *ptr);

/**
 * @brief Gets the system uptime in milliseconds.
 *
 * This function returns the number of milliseconds that have elapsed since the system was started.
 *
 * @return The system uptime in milliseconds.
 */
uint32_t lr_port_kernel_get_uptime_ms(void);

#endif /* LIBRE_RTOS_PORT_H */
