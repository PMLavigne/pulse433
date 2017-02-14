
#ifdef ARDUINO
#ifndef PULSE433_ARDUINOINTERRUPTDRIVER_H
#define PULSE433_ARDUINOINTERRUPTDRIVER_H

#include "Driver.h"
namespace Pulse433
{
    class ArduinoInterruptDriver : public Driver
    {
    private:

    public:
        ArduinoInterruptDriver() {}
        virtual void install();
        virtual void uninstall();
    };
}

#endif
#endif
