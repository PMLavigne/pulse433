
#ifndef PULSE433_AVRLOOPDRIVER_H
#define PULSE433_AVRLOOPDRIVER_H

#import <drivers/Driver.h>
#ifdef AVR

#define PULSE433_AVR_LOOP_DRIVER_AVAILABLE

namespace Pulse433 {
    class AVRLoopDriver : public Driver {

    public:
        AVRLoopDriver() {}
        virtual ~AVRLoopDriver() {}

        virtual void install();
        virtual void setTransmitterOn(const bool state);
    };
}

#endif

#endif //PULSE433_AVRLOOPDRIVER_H
