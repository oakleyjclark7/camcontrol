#pragma once

#include <optional>
#include <string>

namespace camcontrol::firmware::comms
{

namespace characters
{
constexpr int NEWLINE = '\n';
constexpr int SPACE = ' ';
} // namespace characters

enum class ControlWord { MOVE_MOTOR };

struct Command {
    ControlWord controlword;
    std::optional<std::string> data;
};

std::optional<Command> readCommand();

} // namespace camcontrol::firmware::comms