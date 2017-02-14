#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

#ifdef USE_SIMULAVR

#include "simulavr_config.h"

#ifndef UNITY_OUTPUT_CHAR

void debug_putc(int debugCharacter) {
    SIMULAVR_DEBUG_WRITE_CHAR(debugCharacter);
}

#define UNITY_OUTPUT_CHAR(a) debug_putc(a)

#endif

#endif

#endif
