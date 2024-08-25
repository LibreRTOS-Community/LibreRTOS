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

#include "task.h"
#include "scheduler.h"
#include "port.h"
#include "config.h"

/**
 * @brief Creates a new task.
 *
 * This function allocates memory for the task stack, initializes the stack with the
 * task function and parameters, and adds the task to the scheduler's task list.
 *
 * @param task_func   Pointer to the function that the task will execute.
 * @param stack_size  Size of the stack to be allocated for the task, in words.
 * @param priority    Priority of the task. Lower numbers represent higher priority.
 * @param params      Pointer to the parameters to be passed to the task function.
 *
 * @return A pointer to the created task's TCB, or NULL if the task creation failed.
 */
lr_tcb_t *lr_task_create(lr_task_func_t *task_func, size_t stack_size, uint32_t priority, void *params) {
    uint32_t *stack = (uint32_t*) malloc(stack_size * sizeof(uint32_t));
    if (stack == NULL) {
        return NULL;
    }

    lr_tcb_t *new_task = (lr_tcb_t*) (stack + stack_size - sizeof(lr_tcb_t) / sizeof(uint32_t));
    new_task->stack_pointer = stack;
    new_task->priority = priority;
    new_task->time_slice = LIBRE_RTOS_CONFIG_TIME_SLICE;

    lr_port_kernel_init_task_stack(&new_task->stack_pointer, task_func, params);
    
    lr_scheduler_add_task(new_task);
    return new_task;
}
