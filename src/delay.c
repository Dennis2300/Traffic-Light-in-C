#include "delay.h"

void delay_ms(unsigned long ms) {
    volatile unsigned long i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 800; j++) {
        }
    }
}
