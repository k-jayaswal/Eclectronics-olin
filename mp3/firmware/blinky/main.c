// Blinky for the MP3 RP2354A board.
//
// Pin map (from mp3_fa2026.kicad_sch):
//   D1  single LED, anode via R11 to GPIO25, cathode to GND   -> active HIGH
//   D2  RGB LED, common anode to +3V3                          -> active LOW
//         GPIO22 via R8 (pad 1), GPIO23 via R9 (pad 2), GPIO24 via R10 (pad 4)
//   D3  power LED, always on (not GPIO-controlled)

#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN 25
static const uint RGB_PINS[3] = {22, 23, 24};

int main(void) {
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    for (int i = 0; i < 3; i++) {
        gpio_init(RGB_PINS[i]);
        gpio_set_dir(RGB_PINS[i], GPIO_OUT);
        gpio_put(RGB_PINS[i], 1);  // off (active low)
    }

    uint step = 0;
    while (true) {
        // D1 toggles every step; D2 cycles through its three channels.
        gpio_put(LED_PIN, step & 1);
        for (int i = 0; i < 3; i++) {
            gpio_put(RGB_PINS[i], i != (int)(step % 3));
        }
        printf("blink %u\n", step);
        step++;
        sleep_ms(500);
    }
}
