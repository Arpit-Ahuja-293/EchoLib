#include "equinox/logger/infoSink.hpp"
#include "equinox/logger/message.hpp"
#include "equinox/logger/stdout.hpp"

namespace equinox {
InfoSink::InfoSink() { setFormat("[equinox] {level}: {message}"); }

static std::string getColor(Level level) {
    switch (level) {
        case Level::DEBUG: return "\033[0;36m"; // cyan
        case Level::INFO: return "\033[0;32m"; // green
        case Level::WARN: return "\033[0;33m"; // yellow
        case Level::ERROR: return "\033[0;31m"; // red
        case Level::FATAL: return "\033[0;31;2m"; // dark red
    }
    __builtin_unreachable();
}

void InfoSink::sendMessage(const Message& message) {
    bufferedStdout().print("{}{}\033[0m\n", getColor(message.level), message.message);
}
} // namespace equinox