#ifndef PULSE433_ABSTRACTAVRDRIVER_H
#define PULSE433_ABSTRACTAVRDRIVER_H

#ifdef AVR

#include <defines.h>
#include <drivers/Driver.h>

namespace Pulse433 {
    class AbstractAVRDriver : public Driver {
    protected:
        const PULSE433_BYTE_T pin;

    public:
        AbstractAVRDriver(const PULSE433_BYTE_T pin) : pin(pin), Driver() { }
        virtual ~AbstractAVRDriver() {}


        virtual void setTransmitterOn(const bool state);
    };
}
#endif

#endif
