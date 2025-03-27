#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t _0th = 1 & (*reg);
    uint16_t _2th = 1 & (*reg >> 2);
    uint16_t _3th = 1 & (*reg >> 3);
    uint16_t _5th = 1 & (*reg >> 5);

    uint16_t add  = _0th ^ _2th ^ _3th ^ _5th;

    *reg = *reg >> 1;
    *reg = *reg | (add << 15);
}

