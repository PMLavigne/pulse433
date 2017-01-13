#ifndef PULSE433_TRANSMITTER_H
#define PULSE433_TRANSMITTER_H

#define PULSE433_TRANSMITTER_BUFF_SIZE 32
#define PULSE433_TRANSMITTER_BITS_PER_BYTE 8

#define PULSE433_TRANSMITTER_TICKS_PER_SHORT_PULSE 1
#define PULSE433_TRANSMITTER_TICKS_PER_LONG_PULSE 4
#define PULSE433_TRANSMITTER_TICKS_PER_START_PULSE 8

namespace Pulse433 {

    class Transmitter {
    private:

        enum class TransmissionState {
            Off,
            Start,
            Zero,
            One,
            Stop
        } state;

        void (*transmitFunction)(bool);

        unsigned char tickCount = 0;

        unsigned char buff[PULSE433_TRANSMITTER_BUFF_SIZE];
        unsigned char buffPos = 0;
        unsigned char buffBytePos = 0;
        unsigned char buffLength = 0;

        void nextState();

    public:
        Transmitter(void (*transmitFunction)(bool)) : transmitFunction(transmitFunction) {
            this->reset();
        }

        bool isBusy() const;
        void reset();
        void tick();
    };
}

#endif
