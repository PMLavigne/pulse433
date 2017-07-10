#ifndef PULSE433_AVRINTERRUPTDRIVER_H
#define PULSE433_AVRINTERRUPTDRIVER_H

#include <drivers/Driver.h>

#ifdef AVR

#define PULSE433_AVR_INTERRUPT_DRIVER_AVAILABLE

namespace Pulse433 {

    class AVRInterruptDriver : public Driver {
    private:
    public:
        AVRInterruptDriver() {}

        virtual ~AVRInterruptDriver() {}

        virtual void install();

        virtual void onTick();
    };
}
#endif

#endif
