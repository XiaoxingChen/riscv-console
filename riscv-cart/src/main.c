#include <stdint.h>
#include "video_api.h"

volatile int global = 42;
volatile uint32_t controller_status = 0;

uint32_t getTicks(void);
uint32_t getStatus(void);
uint32_t getVideoInterruptSeq(void);
void initVideoSetting();

extern uint8_t bird_img_0[64*64];
extern uint8_t bird_img_1[64*64];
extern uint8_t bird_img_2[64*64];

volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xFE800);
volatile char *MODE_CONTROL_REG = (volatile char *)(0x50000000 + 0xFF414);

uint32_t hookFunction(uint32_t func_id);

FuncWriteTargetMem writeTargetMem;
FuncWriteTarget writeTarget;

int main() {
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 12;

    writeTargetMem = (FuncWriteTargetMem)hookFunction(1);
    writeTarget = (FuncWriteTarget)hookFunction(2);

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

    initVideoSetting();
    uint32_t sprite_x = 30;
    uint32_t sprite_y = 30;
    int move_speed = 5;


    while (1) {
        global = getTicks();
        if(global != last_global){
            VIDEO_MEMORY[15] = '0' + (getVideoInterruptSeq() % 10);
            controller_status = getStatus();
            if(controller_status){
                VIDEO_MEMORY[x_pos] = ' ';
                if(controller_status & 0x1){
                    sprite_x -= move_speed;
                    if(x_pos & 0x3F){
                        x_pos--;
                    }
                }
                if(controller_status & 0x2){
                    sprite_y -= move_speed;
                    if(x_pos >= 0x40){
                        x_pos -= 0x40;
                    }
                }
                if(controller_status & 0x4){
                    sprite_y += move_speed;
                    if(x_pos < 0x8C0){
                        x_pos += 0x40;
                    }
                }
                if(controller_status & 0x8){
                    sprite_x += move_speed;
                    if((x_pos & 0x3F) != 0x3F){
                        x_pos++;
                    }
                }
                // setLargeSpriteControl(0, 64, 64, sprite_x, sprite_y, 1);
                VIDEO_MEMORY[x_pos] = 'X';
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
