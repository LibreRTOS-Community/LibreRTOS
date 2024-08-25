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

#include "scheduler.h"
#include "config.h"
#include "port.h"

static lr_tcb_t *current_task = NULL;
static lr_tcb_t *task_list = NULL;
static volatile uint32_t system_ticks = 0;

/**
 * @brief Idle task that runs when no other task is ready.
 *
 * This task enters the CPU into low power mode to save energy when the system is idle.
 *
 * @param params Unused parameter.
 */
void idle_task(void *params) {
    while (1) {
        lr_port_kernel_enter_low_power();
    }
}

/**
 * @brief Adds a new task to the scheduler's task list.
 *
 * The task is inserted into the list based on its priority. Higher priority tasks
 * are placed earlier in the list.
 *
 * @param new_task Pointer to the TCB of the new task to be added.
 */
void lr_scheduler_add_task(lr_tcb_t *new_task) {
    if (task_list == NULL) {
        task_list = new_task;
        new_task->next = NULL;
        return;
    }

    lr_tcb_t *prev = NULL;
    lr_tcb_t *task = task_list;

    while (task != NULL && task->priority <= new_task->priority) {
        prev = task;
        task = task->next;
    }

    if (prev == NULL) {
        new_task->next = task_list;
        task_list = new_task;
    } else {
        prev->next = new_task;
        new_task->next = task;
    }
}

/**
 * @brief Performs a context switch to the highest priority task.
 *
 * The current task's context is saved, and the context of the highest priority task
 * is restored.
 */
void lr_scheduler_switch_task(void) {
    lr_port_kernel_save_context(current_task->context);
    current_task = get_highest_priority_task();
    lr_port_kernel_restore_context(current_task->context);
}

/**
 * @brief Returns the task with the highest priority from the task list.
 *
 * This function scans the task list to find and return the task with the highest priority.
 *
 * @return Pointer to the TCB of the highest priority task.
 */
lr_tcb_t *get_highest_priority_task(void) {
    lr_tcb_t *highest_priority_task = task_list;
    lr_tcb_t *task = task_list;

    while (task != NULL) {
        if (task->priority < highest_priority_task->priority) {
            highest_priority_task = task;
        }

        task = task->next;
    }

    highest_priority_task->time_slice = LIBRE_RTOS_CONFIG_TIME_SLICE;
    return highest_priority_task;
}

/**
 * @brief Starts the task scheduler.
 *
 * This function creates the idle task, sets up the system tick timer, and starts
 * the scheduler to begin task execution.
 */
void lr_scheduler_start(void) {
    lr_task_create(idle_task, 1024, 255, NULL);

    current_task = task_list;
    lr_port_kernel_setup_tick_timer(LIBRE_RTOS_CONFIG_TICK_RATE_HZ); 

    lr_port_kernel_start_scheduler();
}

/**
 * @brief System tick handler.
 *
 * This function is called on every system tick to update the system tick count,
 * decrement the current task's time slice, and trigger a context switch if necessary.
 */
void lr_port_kernel_tick_handler(void) {
    system_ticks++;

    if (current_task->time_slice > 0) {
        current_task->time_slice--; 
    }

    if (current_task->time_slice == 0) {
        lr_scheduler_switch_task();
    }
}
