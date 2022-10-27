#include <stdint.h>
#include <string.h>
#include "video_api.h"

volatile int global = 42;
volatile uint32_t controller_status = 0;

volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xFE800);

volatile char *BACKGROUND_PALETTE_0 = (volatile char *)(0x50000000 + 0xFC000);
volatile char *SPRITE_PALETTE_0 = (volatile char *)(0x50000000 + 0xFD000);
volatile char *SPRITE_PALETTE_1 = (volatile char *)(0x50000000 + 0xFD400);

volatile char *BACKGROUND_CONTROL_0 = (volatile char *)(0x50000000 + 0xFF100);
volatile char *LARGE_SPRITE_CONTROL_0 = (volatile char *)(0x50000000 + 0xFF114);
volatile char *LARGE_SPRITE_CONTROL_1 = (volatile char *)(0x50000000 + 0xFF118);
volatile char *LARGE_SPRITE_CONTROL_2 = (volatile char *)(0x50000000 + 0xFF11b);

volatile char *BACKGROUND_DATA_IMG_0 = (volatile char *)(0x50000000 + 0x00000);
volatile char *LARGE_SPRITE_DATA_IMG_0 = (volatile char *)(0x50000000 + 0xB4000);
volatile char *LARGE_SPRITE_DATA_IMG_1 = (volatile char *)(0x50000000 + 0xB5000);
volatile char *LARGE_SPRITE_DATA_IMG_2 = (volatile char *)(0x50000000 + 0xB6000);

volatile char *MODE_CONTROL_REG = (volatile char *)(0x50000000 + 0xFF414);

void initVideoSetting();
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

    uint32_t sprite_x = 30;
    uint32_t sprite_y = 30;
    int move_speed = 5;

    initVideoSetting();

    while (1) {
        int c = a + b + global;
        if(global != last_global){
            if(controller_status){
                VIDEO_MEMORY[x_pos] = ' ';
                if(controller_status & 0x1){ //left
                    sprite_x -= move_speed;
                    if(x_pos & 0x3F){
                        x_pos--;
                    }
                }
                if(controller_status & 0x2){ // up
                    sprite_y -= move_speed;
                    if(x_pos >= 0x40){
                        x_pos -= 0x40;
                        
                    }
                }
                if(controller_status & 0x4){ // down
                    sprite_y += move_speed;
                    if(x_pos < 0x8C0){
                        x_pos += 0x40;
                    }
                }
                if(controller_status & 0x8){ // right
                    sprite_x += move_speed;
                    if((x_pos & 0x3F) != 0x3F){
                        x_pos++;
                    }
                }
                VIDEO_MEMORY[x_pos] = 'X';
                // setLargeSpriteControl(LARGE_SPRITE_CONTROL_0, 64, 64, sprite_y, sprite_x, 0);
            }
            
            for(int i = 0; i < 3; i++)
            {
                setLargeSpriteControl(i, 64, 64, sprite_x, sprite_y, i == global % 3);
            }
            last_global = global;
        }
    }
    return 0;
}
