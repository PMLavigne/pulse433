#ifndef PULSE433_DRIVER_H
#define PULSE433_DRIVER_H

#include "Transmitter.h"
namespace Pulse433
{
    class Driver
    {
    protected:
    public:
        Driver() {}
        virtual ~Driver() {}

        virtual void install() = 0;
        virtual void uninstall() = 0;
    };
}
#endif
