#ifndef PULSE433_TRANSMITTER_H
#define PULSE433_TRANSMITTER_H

#include <string.h>
#include "defines.h"
#include "drivers/Driver.h"
#include "drivers/TickCallback.h"

namespace Pulse433 {

    enum class TransmissionState : unsigned char {
        Off,
        Start,
        Zero,
        One,
        Stop
    };

    class Transmitter : TickCallback {
    private:
        TransmissionState state;
        Driver & driver;

        PULSE433_SIZE_T tickCount = 0;

        PULSE433_BYTE_T buff[PULSE433_TRANSMITTER_BUFF_MAX_SIZE];
        PULSE433_SIZE_T buffPos = 0;
        PULSE433_SIZE_T buffBytePos = 0;
        PULSE433_SIZE_T buffLength = 0;

        void nextState();

    public:

        Transmitter(Driver & driver) : driver(driver) {
            driver.setTickCallback(this);
            this->reset();
        }

        virtual ~Transmitter() {}

        bool isBusy() const {
            return this->buffLength != 0;
        }

        TransmissionState getState() const {
            return this->state;
        }

        PULSE433_SIZE_T getTickCount() const {
            return this->tickCount;
        }

        PULSE433_SIZE_T getBuffPos() const {
            return this->buffPos;
        }

        PULSE433_SIZE_T getBuffBytePos() const {
            return this->buffBytePos;
        }

        PULSE433_SIZE_T getBuffLength() const {
            return this->buffLength;
        }

        bool transmitData(const PULSE433_BYTE_T * data, const PULSE433_SIZE_T size);

        void reset();

        void tick();
    };
}

#endif
