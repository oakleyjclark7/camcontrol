#include <comms/read_command.hpp>

#include <pico/stdlib.h>

using namespace camcontrol::firmware;

uint32_t SHORT_DELAY = 200;
uint32_t LONG_DELAY = 3000;

void turnPinOn(uint pin)
{
    gpio_put(pin, 1);
}

void turnPinOff(uint pin)
{
    gpio_put(pin, 0);
}

int main()
{
    stdio_init_all();

    // So we can blink
    const uint ledPin = PICO_DEFAULT_LED_PIN;
    gpio_init(ledPin);
    gpio_set_dir(ledPin, GPIO_OUT);

    while (true)
    {
        auto cmd = comms::readCommand();
        if (cmd && cmd->controlword == comms::ControlWord::MOVE_MOTOR)
        {
            // Blink led to show we have it
            turnPinOn(ledPin);
            sleep_ms(LONG_DELAY);
            turnPinOff(ledPin);
            sleep_ms(SHORT_DELAY);
        } else {
            turnPinOn(ledPin);
            sleep_ms(SHORT_DELAY);
            turnPinOff(ledPin);
            sleep_ms(SHORT_DELAY);
        }
    }

    return 0;
}