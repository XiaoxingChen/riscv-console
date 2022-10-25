#include <stdint.h>
#include <string.h>

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

void initPaletteGrayScale(volatile char * addr, uint32_t base)
{
    uint32_t shift = (base % 3) * 8;
    for(int i = 0; i < 256; i++)
    {
        ((volatile uint32_t*)addr)[i] = (0xff000000 | (i << shift));
    }
}

void initPaletteBird(volatile char * addr)
{
    uint8_t color_palette[4*8] = {
    0, 0, 0, 0, 
    204, 230, 215, 255, 
    44, 128, 224, 255, 
    250, 250, 250, 255, 
    0, 56, 252, 255, 
    140, 215, 250, 255, 
    51, 183, 248, 255, 
    70, 56, 83, 255};

    // memcpy((uint8_t*)addr, color_palette, 32);
    for(int i = 0; i < 32; i++) addr[i] = color_palette[i];
}

void initPaletteTransparent(volatile char * addr)
{
    for(int i = 0; i < 256 * 4; i++) addr[i] = 0x00;
}

void initPaletteBirdBackground(volatile char * addr)
{
    const uint8_t total_num = 4*16;
    uint8_t color_palette[4*16] = {
    185, 229, 182, 255,
    125, 216, 112, 255,
    210, 217, 158, 255,
    202, 229, 185, 255,
    203, 201, 115, 255,
    161, 216, 152, 255,
    211, 221, 168, 255,
    129, 228, 120, 255,
    199, 191, 92, 255,
    117, 216, 103, 255,
    118, 226, 109, 255,
    200, 194, 97, 255,
    203, 239, 212, 255,
    217, 251, 232, 255,
    190, 235, 200, 255,
    139, 206, 120, 255};

    for(int i = 0; i < total_num; i++) addr[i] = color_palette[i];
}

extern uint8_t bird_img_0[64*64];
extern uint8_t bird_img_1[64*64];
extern uint8_t bird_img_2[64*64];
extern uint8_t bird_background_img[288*512];

void setBackgroundControl(volatile char* addr)
{
    uint32_t x_pos = 512;
    uint32_t y_pos = 288;
    *((volatile uint32_t*) addr) = (x_pos << 2) + (y_pos << 12);
}

void setLargeSpriteControl(uint8_t idx, uint32_t h, uint32_t w, uint16_t y, uint32_t x, uint32_t palette)
{
    uint8_t* addr = (uint8_t*)LARGE_SPRITE_CONTROL_0 + idx * 4;
    h = (h - 33) & 0x1F;
    w = (w - 33) & 0x1F;
    y = (y + 64) & 0x1FF;
    x = (x + 64) & 0x3FF;
    palette = palette & 0x3;
    *((volatile uint32_t*) addr) = (h << 26) + (w << 21) + (y << 12) + (x << 2) + palette;
}
#if 0
void setLargeSpriteDataImage(volatile char* addr)
{
    int height = 64;
    int width = 64;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            unsigned char idx = ((i<<2) & 0xff);
            // idx = 200;
            addr[i * width + j] = idx;
        }
    }
}
#endif



void setLargeSpriteDataImage(volatile char* addr, uint8_t* img_src)
{
    int height = 64;
    int width = 64;

    for(int i = 0; i < height * width; i++) addr[i] = img_src[i];
}

void setBackgroundDataImageBirdBackground(volatile char* addr)
{
    int height = 288;
    int width = 512;

    for(int i = 0; i < height * width; i++) addr[i] = bird_background_img[i];
}

void setBackgroundDataImage(volatile char* addr)
{
    int height = 288;
    int width = 512;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            unsigned char idx = (i & 0xff);
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

    // initPaletteGrayScale(BACKGROUND_PALETTE_0, 1);
    // initPaletteGrayScale(SPRITE_PALETTE_0, 2);
    initPaletteBirdBackground(BACKGROUND_PALETTE_0);
    initPaletteBird(SPRITE_PALETTE_1);
    initPaletteTransparent(SPRITE_PALETTE_0);

    setBackgroundControl(BACKGROUND_CONTROL_0);
    setLargeSpriteControl(0, 64, 64, 30, 30, 1);
    setLargeSpriteControl(1, 64, 64, 30, 30, 0);
    setLargeSpriteControl(2, 64, 64, 30, 30, 0);

    // setBackgroundDataImage(BACKGROUND_DATA_IMG_0);
    // setLargeSpriteDataImage(LARGE_SPRITE_DATA_IMG_0);
    setBackgroundDataImageBirdBackground(BACKGROUND_DATA_IMG_0);
    setLargeSpriteDataImage(LARGE_SPRITE_DATA_IMG_0, bird_img_0);
    setLargeSpriteDataImage(LARGE_SPRITE_DATA_IMG_1, bird_img_1);
    setLargeSpriteDataImage(LARGE_SPRITE_DATA_IMG_2, bird_img_2);

    enableGraphicMode();
    uint32_t sprite_x = 30;
    uint32_t sprite_y = 30;
    int move_speed = 5;

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
                setLargeSpriteControl(i, 64, 64, sprite_y, sprite_x, i == global % 3);
            }
            last_global = global;
        }
    }
    return 0;
}
