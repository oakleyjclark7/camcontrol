#pragma once

#include <cinttypes>

// We want to be able to move BY an angle, therefore, we need to keep track of where we need to keep track of the current position

namespace camcontrol::firmware::motor_control {

// SG90 specific stuff
// The servos use pwm for position control
// The pwm period is 20ms
// 0.5 ms duty cycle is -90 deg, 1.5 ms is 0 deg, and 2.5 ms is 90 deg
namespace SG90 {
    // duty cycle min/max
    inline constexpr uint16_t MIN_US = 500;
    inline constexpr uint16_t MAX_US = 2500;
    // angle limits
    inline constexpr int16_t MIN_DEG = -90;
    inline constexpr int16_t MAX_DEG = 90;
    // PWM clock (assuming 125MHz pico clock)
    inline constexpr uint32_t CLKDIV = 125; // PWM ticks are 1us
    inline constexpr uint32_t WRAP = 20000; // 20 ms period
    inline constexpr uint32_t TICKS_PER_US = 1;
}

enum class MotorRole {
    PAN = 0,
    TILT = 1
};

struct PositionLimitDegrees
{
    int16_t min;
    int16_t max;

    PositionLimitDegrees(int16_t min, int16_t max)
    : min(min)
    , max(max)
    {}
};

class MotorControl {
  public:
    MotorControl(uint8_t pin, PositionLimitDegrees limits);
    void moveByDeg(int16_t degrees);

  private:
    uint8_t pin_;
    uint16_t pwmSlice_;
    uint16_t pwmChannel_;

    int16_t positionDegrees_;
    PositionLimitDegrees limits_;

    uint32_t getPwmLevel(int16_t positionDegrees);
    void updateSignal();
};

}