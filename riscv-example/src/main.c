#include <stdint.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;

volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xFE800);

volatile char *BACKGROUND_PALETTE_0 = (volatile char *)(0x50000000 + 0xFC000);
volatile char *BACKGROUND_CONTROL_0 = (volatile char *)(0x50000000 + 0xFF100);
volatile char *BACKGROUND_DATA_IMG_0 = (volatile char *)(0x50000000 + 0x00000);
volatile char *MODE_CONTROL_REG = (volatile char *)(0x50000000 + 0xFF414);

void initPaletteGrayScale(volatile char * addr)
{
    for(int i = 0; i < 256; i++)
    {
        ((volatile uint32_t*)addr)[i] = (0xff000000 | i);
    }
}

void setBackgroundControl(volatile char* addr)
{
    uint32_t x_pos = 512;
    uint32_t y_pos = 288;
    *((volatile uint32_t*) addr) = (x_pos << 2) + (y_pos << 12);
}

void setBackgroundDataImage(volatile char* addr)
{
    int height = 288;
    int width = 512;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            unsigned char idx = (i & 0x7f);
            // if((i >> 3) & 1)
            // {
            //     idx = 255;
            // }else
            // {
            //     idx = 0;
            // }
            addr[i * width + j] = idx;
        }
    }
}

void enableGraphicMode()
{
    *MODE_CONTROL_REG = 0x1;
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

    initPaletteGrayScale(BACKGROUND_PALETTE_0);
    setBackgroundControl(BACKGROUND_CONTROL_0);
    setBackgroundDataImage(BACKGROUND_DATA_IMG_0);
    enableGraphicMode();

    while (1) {
        int c = a + b + global;
        if(global != last_global){
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
