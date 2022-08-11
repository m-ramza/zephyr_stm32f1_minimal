/**
 * @file main.c
 * @brief Application entry point
 * @copyright 
 * @license Apache-2.0
 * @author Mohd Ramza <mohdramza@yahoo.com>
 */

#include <zephyr.h>
#include <kernel.h>
#include <logging/log.h>
#include "thread_manager.h"

LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_INF);

/* A conditional variable to suspend main thread post initialization */
K_CONDVAR_DEFINE(main_thread_suspend_resume);
K_MUTEX_DEFINE(main_thread_mutex);

/**
 * @brief Entry point of application
 */
void main(void)
{
	LOG_INF("Hello. This is Stm32f1 Series Project");

	spawn_application_threads();

	while (1) {
		/*Lets suspend the thread as it has done its job*/
		LOG_WRN("Init done. Suspending myself!");
		k_condvar_wait(&main_thread_suspend_resume, &main_thread_mutex, K_FOREVER);
	}
}