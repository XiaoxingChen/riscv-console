#include <stdint.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;

uint32_t getTicks(void);
uint32_t getStatus(void);

/**
 * interrupt handlers
 */
uint32_t registerHandler(uint32_t code);

uint32_t  myHandler(uint32_t code);

volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xFE800);

int main() {

    VIDEO_MEMORY[70]='i';

    int value = registerHandler((uint32_t) myHandler);


    VIDEO_MEMORY[79]='h';


    return 0;
}
uint32_t  myHandler(uint32_t code){
    VIDEO_MEMORY[80]='j';
}
