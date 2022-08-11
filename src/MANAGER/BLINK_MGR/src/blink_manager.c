/**
 * @file blink_manager.c
 * @brief System blink thread
 * @license Apache-2.0
 * @author Mohd Ramza <mohdramza@yahoo.com>
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(BLINK_MGR, LOG_LEVEL_INF);

const struct gpio_dt_spec blue_led_spec = GPIO_DT_SPEC_GET(DT_NODELABEL(blue_led), gpios);

/**
 *@brief Toggles a LED repititively to simulate blinking.
 */
void thread_blink(void)
{
	int cnt = 0;
	uint32_t sleep_ms = 100;

	if (!device_is_ready(blue_led_spec.port)) {
		LOG_ERR("Device %s not ready", blue_led_spec.port->name);
		return;
	} else {
		gpio_pin_configure_dt(&blue_led_spec, GPIO_OUTPUT);
		LOG_INF("LED device ready [%s]", blue_led_spec.port->name);
	}

	while (1) {
		gpio_pin_set(blue_led_spec.port, blue_led_spec.pin, cnt % 2);

		k_msleep(sleep_ms);
		cnt++;
	}
}