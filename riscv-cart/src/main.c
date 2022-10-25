#include <stdint.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;
volatile int myCounter =1;
uint32_t getTicks(void);

uint32_t getStatus(void);

/**
 * interrupt handlers
 */
uint32_t registerHandler(uint32_t code);

uint32_t myHandler(uint32_t code);

uint32_t myHandler2(uint32_t code);

volatile int invokingFlag = 0;
volatile char *VIDEO_MEMORY = (volatile char *) (0x50000000 + 0xFE800);

int main() {
    registerHandler((uint32_t) myHandler);
    registerHandler((uint32_t) myHandler2);
    invokingFlag = 1;
    // hold the invoking, otherwise the main will be invoked repeatedly.
    while (1) {

    }

    return 0;
}

uint32_t myHandler(uint32_t code) {
    if(myCounter<=100){
        VIDEO_MEMORY[myCounter] = 'x';
        myCounter++;
    }
    return 0;
}

uint32_t myHandler2(uint32_t code) {
    if(myCounter<=100){
        VIDEO_MEMORY[myCounter+100] = 'p';
    }
    return 0;
}
