#include <motor_control/motor_control.hpp>

#include "pico/stdlib.h"
#include "hardware/pwm.h"

using namespace camcontrol::firmware::motor_control;

// Servo motor pins
const uint8_t PAN_SERVO_PIN = 18;
const uint8_t TILT_SERVO_PIN = 20;

// Cycle test led
void cycleLed(const int ledPin, int timeMs)
{
    gpio_put(ledPin, 1);
    sleep_ms(timeMs);

    gpio_put(ledPin, 0);
    sleep_ms(timeMs);
}

void sweepMotors(MotorControl& pan, MotorControl& tilt)
{
    for (int i = 0; i < 180; i++){
        pan.moveByDeg(2);
        tilt.moveByDeg(1);
        sleep_ms(8);
    }
    for (int i = 0; i < 180; i++){
        pan.moveByDeg(-2);
        tilt.moveByDeg(-1);
        sleep_ms(8);
    }
}

int main() {
    stdio_init_all();

    // LED setup
    const uint ledPin = PICO_DEFAULT_LED_PIN;
    gpio_init(ledPin);
    gpio_set_dir(ledPin, GPIO_OUT);

    // Create motor instances, attach to correct pins
    auto panMotor = MotorControl{PAN_SERVO_PIN, PositionLimitDegrees{-90, 90}};
    auto tiltMotor = MotorControl{TILT_SERVO_PIN, PositionLimitDegrees{0, 90}};

    sleep_ms(3000);

    while (true) {

        // Blink LED
        for (int i = 0; i < 3; i++) {
            cycleLed(ledPin, 100);
            cycleLed(ledPin, 100);
            sleep_ms(500);
        }

        // Sweep motors
        sweepMotors(panMotor, tiltMotor);
    }
}