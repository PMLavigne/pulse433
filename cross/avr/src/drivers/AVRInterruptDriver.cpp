#ifdef AVR
#include <avr/io.h>
#include <avr/interrupt.h>
#include "AVRInterruptDriver.h"

namespace Pulse433 {

    void AVRInterruptDriver::install() {
        cli();
        TIMSK2 |= (1 << TOIE2);
        TCCR2B |= (1 << CS22)|(1 << CS21);
        TCNT2 = 0;
        sei();
    }

    void AVRInterruptDriver::onTick() {

    }
}
#endif
