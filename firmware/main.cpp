#include <comms/read_command.hpp>
#include <motor_control/motor_control.hpp>

#include <pico/stdlib.h>

using namespace camcontrol::firmware;

// Servo motor pins
const uint8_t PAN_SERVO_PIN = 18;
const uint8_t TILT_SERVO_PIN = 20;

int main()
{
    stdio_init_all();

    // Create motor instances, attach to correct pins
    auto panMotor = motor_control::MotorControl{PAN_SERVO_PIN, motor_control::PositionLimitDegrees{-90, 90}};
    auto tiltMotor = motor_control::MotorControl{TILT_SERVO_PIN, motor_control::PositionLimitDegrees{0, 90}};

    while (true) {
        // Listen for a command
        auto cmd = comms::readCommand();
        if (cmd && cmd->controlword == comms::ControlWord::MOVE_MOTOR) 
        {
            auto data = cmd->data.value();
            int degrees = std::stoi(data);
            panMotor.moveByDeg(degrees);
            stdio_printf("Moving by %i degrees\n", degrees);
        }
    }


    return 0;
}