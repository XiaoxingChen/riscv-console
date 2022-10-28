#include <stdint.h>
#include <string.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;
volatile uint32_t *CARTRIDGE = (volatile uint32_t *)(0x4000001C);
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xFE800);

extern uint8_t bird_img_0[64*64];
extern uint8_t bird_img_1[64*64];
extern uint8_t bird_img_2[64*64];
extern uint8_t bird_background_img[288*512];
volatile char *BACKGROUND_IMG_0 = (volatile char *)(0x50000000 + 0);
volatile char *LARGE_SPRITE_IMG_0 = (volatile char *)(0x50000000 + 0xB4000 + 0 * 0x1000);
volatile char *LARGE_SPRITE_IMG_1 = (volatile char *)(0x50000000 + 0xB4000 + 1 * 0x1000);
volatile char *LARGE_SPRITE_IMG_2 = (volatile char *)(0x50000000 + 0xB4000 + 2 * 0x1000);

typedef void (*FunPtr)(void);
volatile int vip_seq = 1;
volatile int cmd_seq = 0;
int main() {
    memcpy((void*)BACKGROUND_IMG_0, bird_background_img, 288*512);
    memcpy((void*)LARGE_SPRITE_IMG_0, bird_img_0, 64*64);
    memcpy((void*)LARGE_SPRITE_IMG_1, bird_img_1, 64*64);
    memcpy((void*)LARGE_SPRITE_IMG_2, bird_img_2, 64*64);
    while(1){
        if((*CARTRIDGE) & 0x1){
            ((FunPtr)((*CARTRIDGE) & 0xFFFFFFFC))();
        }
    }
    return 0;
}
