// Global configuration file for InterPi Arduino firmware
// Change settings here, not in the main file.

#ifndef _INTERPI_CONFIG
#define _INTERPI_CONFIG

// Use this to specify the I2C address to respond to
// It must be between 0x00 and 0x7F, inclusive
#define I2C_ADDR 0x55

// Use this to specify the analog reference source
#define AREF INTERNAL

// Use this to specify the initial system state
// It must be between 0x00 and 0xFF, inclusive
// 0x00 is probably not a good idea, because it
// is used to trigger a reset when a read is issued.
#define INIT_STATE 0xFF

// Comment this out to disable HRNG state
#define HRNG_STATE
// Comment this out to disable analog read A0 state
#define AR0_STATE
// Comment this out to disable analog read A1 state
#define AR1_STATE
// Comment this out to disable analog read A2 state
#define AR2_STATE
// Comment this out to disable analog read A3 state
#define AR3_STATE
// Comment this out to disable analog read A4 state
#define AR4_STATE
// Comment this out to disable analog read A5 state
#define AR5_STATE
// Comment this out to disable analog read A6 state
#define AR6_STATE
// Comment this out to disable analog read A7 state
// This is auto-disabled by HRNG_STATE
#define AR7_STATE

// Comment this out to disable using Pin 2 as an interrupt
#define USE_INT0
// Set this to the trigger condition for Int0
#define INT0_TRIG LOW

// Comment this out to disable using Pin 3 as an interrupt
#define USE_INT1
// Set this to the trigger condition for Int1
#define INT1_TRIG LOW

// Don't change anything below here unless you know exactly what you are doing
#ifdef HRNG_STATE
#undef AR7_STATE
#endif // HRNG_STATE

#endif // _INTERPI_CONFIG
