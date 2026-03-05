#include <stdint.h>
#include "syscalls.h"

/* GPIO LED pin definition */
#define LED_PIN 25
/* GPIO Button pin definition */
#define BTN_PIN 15

void faseA();
void faseB();

int user_app_entry(void) {
    // Setup Phase (Unprivileged): The user program configures its resources using syscalls.

    // TODO: Configure LED_PIN as output and BTN_PIN as input using sys_gpio_dir syscall
    sys_gpio_dir(LED_PIN, 1);
    sys_gpio_dir(BTN_PIN, 0);

    faseA();
    // Should never reach here
    return 0;
}


void faseA(){
 
    while (1) {
        // Operational Phase (Unprivileged): The user program performs its main functionality.
        // TODO: Read the button state using sys_gpio_get 
        int button = sys_gpio_get(BTN_PIN);
        // set the LED state accordingly using sys_gpio_set
        sys_gpio_set(LED_PIN, button);

    }
}

void faseB(){

    int stable_count = 0;
    int last_read = sys_gpio_get(BTN_PIN);
    int stable_state = last_read;
    int led_state = 0;

    while (1) {

        int current_read = sys_gpio_get(BTN_PIN);

        // Count stability
        if (current_read == last_read) {
            stable_count++;
        } else {
            stable_count = 0;
        }

        // If a stable state changes 
        if (stable_count > 5 && current_read != stable_state) {

            stable_state = current_read;

            // Detect falling edge 1 -> 0
            if (stable_state == 0) {
                led_state = !led_state;
                sys_gpio_set(LED_PIN, led_state);
            }
        }

        last_read = current_read;

        // delay
        for (volatile int i = 0; i < 100; i++){
            for (volatile int j=0; j<500; j++);
        }
    }
}