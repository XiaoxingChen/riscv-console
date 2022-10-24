#include <stdint.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;

uint32_t getTicks(void);

uint32_t getStatus(void);

/**
 * interrupt handlers
 */
uint32_t registerHandler(uint32_t code);

uint32_t myHandler(uint32_t code);

uint32_t myHandler2(uint32_t code);

int counter1 = 1;

volatile char *VIDEO_MEMORY = (volatile char *) (0x50000000 + 0xFE800);

int main() {
    registerHandler((uint32_t) myHandler);

    registerHandler((uint32_t) myHandler2);

    return 0;
}

uint32_t myHandler(uint32_t code) {
    if (counter1 <= 200) {
        VIDEO_MEMORY[counter1] = 'x';
        counter1++;
    }
}

uint32_t myHandler2(uint32_t code) {
    if (counter1 <=200) {
        VIDEO_MEMORY[counter1+200] = 'p';
        counter1++;
    }
}
