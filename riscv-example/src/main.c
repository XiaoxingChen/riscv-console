#include <stdint.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;
volatile uint32_t interrupt_pending = 0;
volatile int vip_seq = 1;

volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xFE800);

void vizInterruptPending()
{
    VIDEO_MEMORY[15] = '0' + ((interrupt_pending >> 24) & 0xff);
    VIDEO_MEMORY[16] = '0' + ((interrupt_pending >> 16) & 0xff);
    VIDEO_MEMORY[17] = '0' + ((interrupt_pending >> 8) & 0xff);
    VIDEO_MEMORY[18] = '0' + ((interrupt_pending >> 0) & 0xff);
}

int main() {
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 12;

    VIDEO_MEMORY[0] = 'H';
    VIDEO_MEMORY[1] = 'e';
    VIDEO_MEMORY[2] = 'l';
    VIDEO_MEMORY[3] = 'l';
    VIDEO_MEMORY[4] = 'o';
    VIDEO_MEMORY[5] = ' ';
    VIDEO_MEMORY[6] = 'W';
    VIDEO_MEMORY[7] = 'o';
    VIDEO_MEMORY[8] = 'r';
    VIDEO_MEMORY[9] = 'l';
    VIDEO_MEMORY[10] = 'd';
    VIDEO_MEMORY[11] = '!';
    VIDEO_MEMORY[12] = 'X';


    while (1) {
        int c = a + b + global;
        if(global != last_global){
            VIDEO_MEMORY[15] = '0' + (vip_seq % 10);
            // vizInterruptPending();
            if(controller_status){
                VIDEO_MEMORY[x_pos] = ' ';
                if(controller_status & 0x1){
                    if(x_pos & 0x3F){
                        x_pos--;
                    }
                }
                if(controller_status & 0x2){
                    if(x_pos >= 0x40){
                        x_pos -= 0x40;
                    }
                }
                if(controller_status & 0x4){
                    if(x_pos < 0x8C0){
                        x_pos += 0x40;
                    }
                }
                if(controller_status & 0x8){
                    if((x_pos & 0x3F) != 0x3F){
                        x_pos++;
                    }
                }
                VIDEO_MEMORY[x_pos] = 'X';
            }
            last_global = global;
        }
    }
    return 0;
}
