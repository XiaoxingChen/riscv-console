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

volatile int invokingFlag = 0;
volatile char *VIDEO_MEMORY = (volatile char *) (0x50000000 + 0xFE800);
volatile uint32_t counter1=0;
int main() {
    if(!invokingFlag){
        VIDEO_MEMORY[1050+counter1]='B';
        counter1++;
//        registerHandler((uint32_t) myHandler);
//
//        registerHandler((uint32_t) myHandler2);
        //invokingFlag=1;
        VIDEO_MEMORY[1049]='A';
    }


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
