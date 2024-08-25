/*
 * Copyright (C) 2024 LibreRTOS Team
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

#ifndef _LIBRE_RTOS_KERNEL_TASK_H_
#define _LIBRE_RTOS_KERNEL_TASK_H_

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Task Control Block (TCB) structure.
 *
 * This structure holds the essential information for managing tasks in LibreRTOS,
 * including the task's stack pointer, priority, time slice, and context.
 */
typedef struct lr_tcb {
    void* stack_pointer;      /**< Pointer to the task's current stack position */
    struct lr_tcb* next;      /**< Pointer to the next task in the ready list */

    uint32_t time_slice;      /**< Time slice allocated to this task */
    uint32_t priority;        /**< Priority of the task */
    void* context;            /**< Pointer to the task's context (registers, etc.) */
} lr_tcb_t;

/**
 * @brief Task function type definition.
 *
 * This type defines the function signature for a task function in LibreRTOS.
 */
typedef void (*lr_task_func_t)(void);

/**
 * @brief Creates a new task.
 *
 * This function creates a new task in LibreRTOS by allocating the necessary resources,
 * initializing the task stack, and setting up the task's control block (TCB).
 *
 * @param task_func   Pointer to the function that the task will execute.
 * @param stack_size  Size of the stack to be allocated for the task.
 * @param priority    Priority of the task.
 * @param params      Pointer to the parameters to be passed to the task function.
 *
 * @return A pointer to the created task's TCB, or NULL if the task creation failed.
 */
lr_tcb_t *lr_task_create(lr_task_func_t *task_func, size_t stack_size, uint32_t priority, void *params);

#endif /* _LIBRE_RTOS_KERNEL_TASK_H_ */
