#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
    if (!gpio_is_ready_dt(&led)) {
        printk("LED device not ready\n");
        return 0;
    }

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    while (1) {
        gpio_pin_toggle_dt(&led);
        printk("Toggled LED\n");
        k_msleep(500);
    }
    return 0;
}

// #include <zephyr/kernel.h>
// #include <zephyr/drivers/led_strip.h>
// #include <zephyr/device.h>
// #include <zephyr/sys/util.h>

// #define STRIP_NODE DT_ALIAS(led_strip)

// #if !DT_NODE_HAS_STATUS_OKAY(STRIP_NODE)
// #error "Unsupported board: led-strip alias is not defined or enabled"
// #endif

// // Fetch device reference from devicetree
// static const struct device *const strip = DEVICE_DT_GET(STRIP_NODE);

// // Prepare color buffer structure (1 pixel)
// static struct led_rgb pixels[1];

// int main(void)
// {
//     if (!device_is_ready(strip)) {
//         printk("LED strip device %s is not ready\n", strip->name);
//         return 0;
//     }

//     while (1) {
//         // 1. Red Blink
//         pixels[0].r = 255; pixels[0].g = 0; pixels[0].b = 0;
//         led_strip_update_rgb(strip, pixels, 1);
//         k_msleep(1000);

//         // 2. Green Blink
//         pixels[0].r = 0; pixels[0].g = 255; pixels[0].b = 0;
//         led_strip_update_rgb(strip, pixels, 1);
//         k_msleep(1000);

//         // 3. Blue Blink
//         pixels[0].r = 0; pixels[0].g = 0; pixels[0].b = 255;
//         led_strip_update_rgb(strip, pixels, 1);
//         k_msleep(1000);

//         // 4. Turn Off
//         pixels[0].r = 0; pixels[0].g = 0; pixels[0].b = 0;
//         led_strip_update_rgb(strip, pixels, 1);
//         k_msleep(1000);
//     }
//     return 0;
// }
