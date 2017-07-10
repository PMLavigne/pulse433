
#ifndef PULSE433_TICKCALLBACK_H
#define PULSE433_TICKCALLBACK_H

namespace Pulse433 {
    class TickCallback {
    public:
        TickCallback() {};
        virtual ~TickCallback() {};

        virtual void tick() = 0;
    };
}

#endif
