#ifndef PULSE433_DRIVER_H
#define PULSE433_DRIVER_H

#include "TickCallback.h"

namespace Pulse433
{
    class Driver
    {
    protected:
        TickCallback * callback = nullptr;
    public:
        Driver() {}
        virtual ~Driver() {}

        void setTickCallback(TickCallback * const callback) {
            this->callback = callback;
        }

        /**
         * If your driver needs to do any setup, override this
         */
        virtual void install() {};

        /**
         * Turn on or off the physical transmitter based on the provided state. Generally this just means toggling a pin.
         * @param state Whether the transmitter should be on or off next.
         */
        virtual void setTransmitterOn(const bool state) = 0;

        /**
         * Should be called by the driver every time the driver "ticks." In my experience most devices use a base
         * tick time of 200-250μS
         */
        void onTick() {
            if (this->callback != nullptr) {
                this->callback->tick();
            }
        }
    };
}
#endif
