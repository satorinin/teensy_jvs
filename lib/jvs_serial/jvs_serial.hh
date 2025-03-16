#pragma once

#include <iostream>
#include <stdint.h>
#include <cstddef>
#include <string>

#ifdef _PLATFORM_TEENSY
#include "Arduino.h"
#else
#include <chrono>
#include <queue>
#include <thread>
#endif

namespace JVSSerial
{
        /// @brief Abstraction for serial println.
        /// @param str string to print.
#ifdef _PLATFORM_TEENSY
#define PRINT(...) Serial.print(__VA_ARGS__)
#define PRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define PRINT(toPrint) std::cout << toPrint
#define PRINTLN(toPrint) std::cout << toPrint << "\n"
#endif

#ifdef _PLATFORM_TEENSY
#define DELAY(ms) delay(ms)
#else
#define DELAY(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif

/// @brief Interface for abstracting native and embedded serial.
class Interface {
 public:
#ifdef _PLATFORM_TEENSY
                Interface(HardwareSerial &serial);
#else
                Interface(std::queue<uint8_t> &in_fifo, std::queue<uint8_t> &out_fifo);
#endif

                /// Returns the number of bytes immediately available to be read from the
                /// device.
                /// \return 0 if none available else the number of characters available for immediate reading
                int available();

                /// Flush remaining data.
                /// Blocks until any data yet to be transmtted is sent.
                void flush();

                /// Read and return the next available character.
                /// If no character is available prints a message to stderr and returns 0;
                /// \return The next available character
                uint8_t read();

                /// Transmit a single character oin the serial port.
                /// Returns immediately.
                /// IO errors are repored by printing aa message to stderr.
                /// \param[in] ch The character to send. Anything in the range 0x00 to 0xff is permitted
                /// \return 1 if successful else 0
                size_t write(uint8_t ch);

        private:
#ifdef _PLATFORM_TEENSY
                HardwareSerial &_Uart;
#else
                std::queue<uint8_t> &_in_fifo;
                std::queue<uint8_t> &_out_fifo;
#endif
};

} // namespace JVSSerial
