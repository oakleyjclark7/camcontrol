#include <motor_control/motor_control.hpp>

#include "pico/stdlib.h"
#include "hardware/pwm.h"

namespace camcontrol::firmware::motor_control {

MotorControl::MotorControl(uint8_t pin, PositionLimitDegrees limits)
: pin_(pin)
, limits_(limits)
, positionDegrees_(limits.min)
{
    // Initialise the pin for pwm
    gpio_set_function(pin_, GPIO_FUNC_PWM);
    pwmSlice_ = pwm_gpio_to_slice_num(pin_);
    pwmChannel_ = pwm_gpio_to_channel(pin_);
    pwm_set_clkdiv(pwmSlice_, SG90::CLKDIV);
    pwm_set_wrap(pwmSlice_, SG90::WRAP);
    updateSignal();
    pwm_set_enabled(pwmSlice_, true);
}

void MotorControl::moveByDeg(int16_t degrees)
{
    auto requestedPosition = positionDegrees_ + degrees;
    if (requestedPosition < limits_.min){
        positionDegrees_ = limits_.min;
    } else if (requestedPosition > limits_.max) {
        positionDegrees_ = limits_.max;
    } else {
        positionDegrees_ = requestedPosition;
    }

    updateSignal();
}

uint32_t MotorControl::getPwmLevel(int16_t positionDegrees)
{
    double norm =
        (positionDegrees - limits_.min) /
        static_cast<double>(limits_.max - limits_.min);

    double pulseUs = SG90::MIN_US + norm * (SG90::MAX_US - SG90::MIN_US); // safe SG90 range
    uint32_t ticks = static_cast<uint32_t>(pulseUs * SG90::TICKS_PER_US);
    return ticks;
}

void MotorControl::updateSignal()
{
    pwm_set_chan_level(pwmSlice_, pwmChannel_, getPwmLevel(positionDegrees_));
}

}