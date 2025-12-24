#pragma once

#include "equinox/logger/message.hpp"
#include "equinox/logger/baseSink.hpp"

namespace equinox {
/**
 * @brief Sink for sending messages to the terminal.
 *
 * This is the primary way of interacting with equinox's logging implementation. This sink is used for printing useful
 * information to the user's terminal.
 * <h3> Example Usage </h3>
 * @code
 * equinox::infoSink()->setLowestLevel(equinox::Level::INFO);
 * equinox::infoSink()->info("info: {}!", "my cool info here");
 * // Specify the order or placeholders
 * equinox::infoSink()->debug("{1} {0}!","world", "hello");
 * // Specify the precision of floating point numbers
 * equinox::infoSink()->warn("Thingy exceeded value: {:.2f}!", 93.1234);
 * @endcode
 */
class InfoSink : public BaseSink {
    public:
        /**
         * @brief Construct a new Info Sink object
         */
        InfoSink();
    private:
        /**
         * @brief Log the given message
         *
         * @param message
         */
        void sendMessage(const Message& message) override;
};
} // namespace equinox
