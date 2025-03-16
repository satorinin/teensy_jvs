#include "jvs_serial.hh"

namespace JVSSerial
{

#ifdef _PLATFORM_TEENSY
    Interface::Interface(HardwareSerial &serial) : _Uart{serial}
    {
    }
#else
    Interface::Interface(std::queue<uint8_t> &in_fifo, std::queue<uint8_t> &out_fifo) : _in_fifo(in_fifo), _out_fifo(out_fifo)
    {
    }
#endif

    int Interface::available()
    {
#ifdef _PLATFORM_TEENSY
        return _Uart.available();
#else
        return _in_fifo.size();
#endif
    }

    void Interface::flush()
    {
#ifdef _PLATFORM_TEENSY
        _Uart.flush();
#else
        _in_fifo = {};
#endif
    }

    uint8_t Interface::read()
    {
#ifdef _PLATFORM_TEENSY
        return static_cast<uint8_t>(_Uart.read());
#else

        uint8_t ch{};
        if (!_in_fifo.empty())
        {
            ch = _in_fifo.front();
            _in_fifo.pop();
            return ch;
        }
        std::cerr << "Interface::read read failed\n";
        return 0;
#endif
    }

    size_t Interface::write(uint8_t ch)
    {
#ifdef _PLATFORM_TEENSY
        return _Uart.write(ch);
#else
        _out_fifo.push(ch);
        return 1;
#endif
    }

} // namespace JVSSerial
