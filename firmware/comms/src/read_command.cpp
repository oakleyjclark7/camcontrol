#include <comms/read_command.hpp>

#include <pico/stdlib.h>

#include <vector>

namespace camcontrol::firmware::comms
{

struct ControlWordEntry {
    std::string stringRep;
    ControlWord word;
};

constexpr ControlWordEntry controlWords[] = {{{"MOVE_MOTOR"}, ControlWord::MOVE_MOTOR}};

std::optional<Command> getCommandFromBuffer(const std::vector<int> &buffer)
{
    if (buffer.empty() || buffer.back() != characters::NEWLINE) {
        return std::nullopt;
    }

    std::string commandString;
    commandString.reserve(buffer.size());
    for (int value : buffer) {
        commandString.push_back(static_cast<char>(value));
    }
    commandString.pop_back();

    std::string commandWord;
    std::optional<std::string> data;
    auto separator = commandString.find(characters::SPACE);
    if (separator == std::string::npos) {
        commandWord = commandString;
    } else {
        commandWord = commandString.substr(0, separator);
        auto argument = commandString.substr(separator + 1);
        if (!argument.empty()) {
            data = argument;
        }
    }

    for (const auto &entry : controlWords) {
        if (commandWord == entry.stringRep) {
            return Command{.controlword = entry.word, .data = data};
        }
    }

    return std::nullopt;
}

std::optional<Command> readCommand()
{
    std::vector<int> buffer;

    while (true) {
        int character = stdio_getchar_timeout_us(1);

        if (character == PICO_ERROR_TIMEOUT) {
            return std::nullopt;
        }
        buffer.push_back(character);
        if (character == characters::NEWLINE) {
            break;
        }
    }
    return getCommandFromBuffer(buffer);
}

} // namespace camcontrol::firmware::comms