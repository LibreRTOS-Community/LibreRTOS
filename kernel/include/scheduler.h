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

#ifndef _LIBRE_RTOS_KERNEL_SCHEDULER_H_
#define _LIBRE_RTOS_KERNEL_SCHEDULER_H_

#include "task.h"

/**
 * @brief Adds a task to the scheduler.
 *
 * This function adds a new task to the scheduler's ready list,
 * making it eligible for execution.
 *
 * @param new_task Pointer to the task's TCB that will be added to the scheduler.
 *
 * @return None.
 */
void lr_scheduler_add_task(lr_tcb_t *new_task);

/**
 * @brief Switches the currently running task.
 *
 * This function performs a context switch, saving the current task's state and
 * restoring the state of the next task to be executed.
 *
 * @return None.
 */
void lr_scheduler_switch_task(void);

/**
 * @brief Starts the task scheduler.
 *
 * This function starts the LibreRTOS scheduler, initiating task execution.
 * It should be called after all tasks have been created and added to the scheduler.
 *
 * @return None.
 */
void lr_scheduler_start(void);

#endif /* _LIBRE_RTOS_KERNEL_SCHEDULER_H_ */
