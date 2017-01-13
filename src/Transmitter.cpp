#include "Transmitter.h"

namespace Pulse433 {

    void Transmitter::nextState() {
        this->tickCount = 0;
        if(this->buffBytePos == PULSE433_TRANSMITTER_BITS_PER_BYTE) {
            this->buffBytePos = 0;
            this->buffPos++;
            if (this->buffPos == this->buffLength) {
                this->state = TransmissionState::Stop;
                return;
            }
        }

        // Get the current byte to work on, then extract the bit we're processing right now. Bits are read left to right
        const bool curBit = this->buff[this->buffPos] & (1 << ((PULSE433_TRANSMITTER_BITS_PER_BYTE - 1) - this->buffBytePos));

        if(curBit) {
            this->state = TransmissionState::One;
        } else {
            this->state = TransmissionState::Zero;
        }
        this->buffBytePos++;
        return;
    }

    bool Transmitter::isBusy() const {
        return this->buffLength != 0;
    }

    void Transmitter::reset() {
        this->transmitFunction(false);
        this->state = TransmissionState::Off;
        this->tickCount = 0;
        this->buffPos = 0;
        this->buffBytePos = 0;
        this->buffLength = 0;
    }

    void Transmitter::tick() {
        switch(this->state) {

            default:
            case TransmissionState::Off: {
                if(this->buffLength == 0) {
                    return;
                }
                this->state = TransmissionState::Start;
                this->transmitFunction(true);
            } break;

            // Start signal is 8 high, 4 low, 4 high, 1 low, return high: ..._/‾‾‾‾‾‾‾‾\____/‾‾‾‾\_/
            case TransmissionState::Start: {
                switch (this->tickCount) {

                    // Signal has been high for 8 ticks
                    case PULSE433_TRANSMITTER_TICKS_PER_START_PULSE:
                        this->transmitFunction(false); break;

                    // Signal has been low for 4 ticks
                    case PULSE433_TRANSMITTER_TICKS_PER_START_PULSE
                         + PULSE433_TRANSMITTER_TICKS_PER_LONG_PULSE:
                        this->transmitFunction(true); break;

                    // Signal has been high for 4 ticks
                    case PULSE433_TRANSMITTER_TICKS_PER_START_PULSE
                         + (2 * PULSE433_TRANSMITTER_TICKS_PER_LONG_PULSE):
                        this->transmitFunction(false); break;

                    // Signal has been low for 1 tick
                    case PULSE433_TRANSMITTER_TICKS_PER_START_PULSE
                         + (2 * PULSE433_TRANSMITTER_TICKS_PER_LONG_PULSE)
                         + PULSE433_TRANSMITTER_TICKS_PER_SHORT_PULSE: {
                        this->transmitFunction(true);
                        this->nextState();
                        return;
                    }

                    default: break;
                }
            } break;

            // Transmit a zero, which is 1 high 4 low: /‾\____/
            case TransmissionState::Zero: {
                switch (this->tickCount) {

                    // Signal has been high for 1 tick
                    case PULSE433_TRANSMITTER_TICKS_PER_SHORT_PULSE:
                        this->transmitFunction(false); break;

                    // Signal has been low for 4 ticks
                    case PULSE433_TRANSMITTER_TICKS_PER_SHORT_PULSE +
                         PULSE433_TRANSMITTER_TICKS_PER_LONG_PULSE: {
                        this->transmitFunction(true);
                        this->nextState();
                        return;
                    }

                    default: break;
                }
            } break;

            // Transmit a one, which is 4 high 1 low: /‾‾‾‾\_/
            case TransmissionState::One: {
                switch (this->tickCount) {

                    // Signal has been high for 4 ticks
                    case PULSE433_TRANSMITTER_TICKS_PER_LONG_PULSE:
                        this->transmitFunction(false);
                        break;

                    // Signal has been low for 1 tick
                    case PULSE433_TRANSMITTER_TICKS_PER_SHORT_PULSE +
                         PULSE433_TRANSMITTER_TICKS_PER_LONG_PULSE: {
                        this->transmitFunction(true);
                        this->nextState();
                        return;
                    }

                    default:
                        break;
                }
            } break;

            // Transmit the stop signal, which is just 1 high: /‾\___...
            case TransmissionState::Stop: {
                // We've already spent a single cycle high, so we just need to shut down the transmitter now
                this->reset();
                return;
            }
        }
        this->tickCount++;
    }

};
