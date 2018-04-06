/*!****************************************************************************
 * @file		monitorTSK.c
 * @author		d_el
 * @version		V1.0
 * @date		05.04.2018
 * @brief
 * @copyright	Copyright (C) 2017 Storozhenko Roman
 *				All rights reserved
 *				This software may be modified and distributed under the terms
 *				of the BSD license.	 See the LICENSE file for details
 */

/*!****************************************************************************
 * Include
 */
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portable.h"
#include "printp.h"
#include "sysTimeMeas.h"

/*!****************************************************************************
 * MEMORY
 */
/*
 * Since at least FreeRTOS V7.5.3 uxTopUsedPriority is no longer
 * present in the kernel, so it has to be supplied by other means for
 * OpenOCD's threads awareness.
 *
 * Add this file to your project, and, if you're using --gc-sections,
 * ``--undefined=uxTopUsedPriority'' (or
 * ``-Wl,--undefined=uxTopUsedPriority'' when using gcc for final
 * linking) to your LDFLAGS; same with all the other symbols you need.
 */
__attribute((used)) const int uxTopUsedPriority = configMAX_PRIORITIES - 1;
uint32_t monitorPeriod = pdMS_TO_TICKS(1000);

/*!****************************************************************************
 * @brief
 */
void vConfigureTimerForRunTimeStats(void){
	sysTimeMeasEnable();
}

/*!****************************************************************************
 * @brief
 */
unsigned long vGetTimerForRunTimeStats(void){
	static uint32_t counter = 0;
	static uint32_t dwtcycnt = 0;

	counter += ((DWT->CYCCNT - dwtcycnt) * 1000ULL) / CORE_FREQUENCY;
	dwtcycnt = DWT->CYCCNT;

	return counter;
}

/*!****************************************************************************
 * @brief
 */
void monitorTSK(void *pPrm){
		static const char *stateToChar[] = {
		"Running",		/* A task is querying the state of itself, so must be running. */
		"Ready",		/* The task being queried is in a read or pending ready list. */
		"Blocked",		/* The task being queried is in the Blocked state. */
		"Suspended",	/* The task being queried is in the Suspended state, or is in the Blocked state with an infinite time out. */
		"Deleted",		/* The task being queried has been deleted, but its TCB has not yet been freed. */
		"Invalid"		/* Used as an 'invalid state' value. */
	};

	TickType_t xLastWakeTime = xTaskGetTickCount();
	uint8_t maxTask = 10;
	uint32_t taskTimePrev[maxTask];
	memset(taskTimePrev, 0, sizeof(taskTimePrev));

	while(1){
		printp("\n---------- OS Monitor ------------\n");

		UBaseType_t taskCount = uxTaskGetNumberOfTasks();

		if(taskCount <= maxTask){
			unsigned long totalRuntime;
			TaskStatus_t buffer[maxTask];

			taskCount = uxTaskGetSystemState(buffer, taskCount, &totalRuntime);

			uint32_t allTaskTime = 0;
			uint32_t idleTaskTime = 0;
			for (UBaseType_t task = 0; task < taskCount; task++){
				allTaskTime += buffer[task].ulRunTimeCounter - taskTimePrev[task];

				if(buffer[task].uxCurrentPriority == 0){
					idleTaskTime = buffer[task].ulRunTimeCounter - taskTimePrev[task];
				}

				taskTimePrev[task] = buffer[task].ulRunTimeCounter;

				printp("[OS] %20s: %9s, %u, %6u, %u\n",
				buffer[task].pcTaskName,
				stateToChar[buffer[task].eCurrentState],
				buffer[task].uxCurrentPriority,
				buffer[task].usStackHighWaterMark,
				buffer[task].ulRunTimeCounter);
			}

			printp("[OS] Current Heap Free Size: %u\n", xPortGetFreeHeapSize());
			printp("[OS] Total RunTime: %u ms\n", totalRuntime);
			printp("[OS] System Uptime: %u ms\n", xTaskGetTickCount() * portTICK_PERIOD_MS);

			printp("[OS] All task period time:  %u ms\n", allTaskTime);
			printp("[OS] Idle task period time: %u ms\n", idleTaskTime);

			if(allTaskTime >= idleTaskTime){
				uint32_t load = ((allTaskTime - idleTaskTime) * 100000) / allTaskTime;
				printp("[OS] OS load: %u.%03u %%\n", load / 1000, load % 1000);
			}
		}

		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(monitorPeriod));
	}
}

/***************** Copyright (C) Storozhenko Roman ******* END OF FILE *******/
