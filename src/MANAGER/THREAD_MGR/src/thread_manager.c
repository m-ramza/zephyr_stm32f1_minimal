/**
 * @file thread_manager.c
 * @brief Module responsible for spawning user space threads
 * @license Apache-2.0
 * @author Mohd Ramza <mohdramza@yahoo.com>
 */

#include <zephyr.h>
#include <kernel.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(THREAD_MGR, LOG_LEVEL_INF);

/* If you are planning to add a thread, kindly update below list.

 ***************   Current UserSpace Threads  ***************
THREAD IDENTIFIER    |  STACK SIZE  |  PRIORITY |     DELAY   |    ROUTINE

blink_thr            |     256      |     7     |      500    |   thread_blink

*/

/**** Thread IDs of type k_tid_t which are used for referencing a thread  ****/

static k_tid_t blink_thr_id;

/**** Thread data objects of type struct k_thread ****/

static struct k_thread blink_thr_data;

/**** Stack area definition for thread stack ****/

K_THREAD_STACK_DEFINE(blink_thr_stack, 256);

/**** Thread entry routines ****/

void thread_blink();

/**** Delay objects. Not needed for case of K_NO_WAIT ****/

#define BLINK_THR_DELAY ((k_timeout_t){ 500 })

/* Guard to avoid re-spawning of threads*/
static bool are_threads_spawned = false;

/**
 * @brief Creates BLINK thread
 */
void create_blink_thread()
{
	/* blink thread*/
	blink_thr_id = k_thread_create(&blink_thr_data, blink_thr_stack,
				       K_THREAD_STACK_SIZEOF(blink_thr_stack), thread_blink, NULL,
				       NULL, NULL, 7, 0, BLINK_THR_DELAY);
	/* Giving name to the thread */
	int rc = k_thread_name_set(blink_thr_id, "BLINK_THR");
	if (rc == 0) {
		LOG_INF("Thread respawned with Id:%p Name:%s", blink_thr_id,
			k_thread_name_get(blink_thr_id));
	} else {
		LOG_ERR("Couldn't set name for BLINK_THR Id:%p [%d]", blink_thr_id, rc);
	}
}

/********* IMPORTANT NOTE ***********
The method used for respawning is not the proper one. Zephyr documentation suggests to use thread termination over thread abort.
The kernel does not currently make any claims regarding an application’s ability to respawn a thread that aborts.
To acheive thread termination, we will have to re-design out thread callback routines, where-in currently we loop in forever. We will  have to redesign them in such a way that when signalled to terminate, they free up all occupied resources and exit gracefully. Looking at scope of this task, currently we will use following work-around which is crude but seems to be working.
*********  NOTE END  ***************/

/**
 * @brief Function to abort and respawn RS485_CH_A thread
 */
void reset_and_respawn_blink_thread(bool respawn)
{
	k_thread_abort(blink_thr_id);

	k_msleep(100);

	if (respawn) {
		create_blink_thread();
	}
}

/**
 * @brief Function to spawn out threads
 */
void spawn_application_threads()
{
	if (!are_threads_spawned) {
		LOG_INF("Spawning userspace threads");
		k_msleep(100);
		create_blink_thread();

		LOG_INF("All userspace threads created!");

		are_threads_spawned = true;
	}
}