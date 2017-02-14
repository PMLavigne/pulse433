
#ifndef SIMULAVR_CONFIG_H
#define SIMULAVR_CONFIG_H

#ifdef USE_SIMULAVR
/*
 *  This port corresponds to the "-W 0x20,-" command line option.
 */
#ifndef SIMULAVR_OUTPUT_REGISTER
#define SIMULAVR_OUTPUT_REGISTER (*( (volatile char *)0x20))
#endif

#ifndef SIMULAVR_DEBUG_WRITE_CHAR
#define SIMULAVR_DEBUG_WRITE_CHAR(ch) SIMULAVR_OUTPUT_REGISTER = ch
#endif

#else

#ifndef SIMULAVR_DEBUG_WRITE_CHAR
#define SIMULAVR_DEBUG_WRITE_CHAR(ch)
#endif

#endif

#endif
