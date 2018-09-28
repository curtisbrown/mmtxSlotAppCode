#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define REV "2.0.0.0"

// Bit set macros
// Set a's bit number b
#define BIT_SET(a, b)   (a |= (1 << b))
// Reset a's bit number b
#define BIT_CLEAR(a, b) (a &= ~(1 << b))
// Returns a's bit number b if set. 0 otherwise
#define BIT_CHECK(a, b) (a & (1 << b))

//MAX'es...
#define MGM_MAX_SEQ_FUNCS 50
#define MAX_TEST_MEAS 100
#define MAX_DPKT_SIZE 512 //must tie in with sDataPkt
#define MAX_SEQ_TESTS 100
#define MAX_FUNC 64

#endif /* DEFINITIONS_H */

