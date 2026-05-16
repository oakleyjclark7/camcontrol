#include "pico/stdlib.h"

#include <vector>

void cycleLed(const int ledPin, int timeMs)
{
    gpio_put(ledPin,1);
    sleep_ms(timeMs);
    gpio_put(ledPin, 0);
    sleep_ms(timeMs);
}

int main()
{
    const uint ledPin = PICO_DEFAULT_LED_PIN;

    gpio_init(ledPin);
    gpio_set_dir(ledPin, GPIO_OUT);

    int shortDelay = 100;
    int longDelay = 1000;

    while (true)
    {
        cycleLed(ledPin, shortDelay);
        cycleLed(ledPin, shortDelay);
        sleep_ms(longDelay);
    }

    return 0;
}