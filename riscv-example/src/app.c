#include "video_api.h"

extern uint8_t bird_color_palette[4*8];
extern uint8_t bird_background_color_palette[4*16];
extern uint8_t bird_img_0[64*64];
extern uint8_t bird_img_1[64*64];
extern uint8_t bird_img_2[64*64];
extern uint8_t bird_background_img[288*512];


void initVideoSetting()
{
    setDisplayMode(DISPLAY_MODE_GRAPHICS);
    initBackgroundPalette(0, bird_background_color_palette, 4*16);
    initSpritePalette(1, bird_color_palette, 4*8);
    initTransparentSpritePalette(0);

    setBackgroundControl(0, 0, 0, 0, 0);
    setLargeSpriteControl(0, 64, 64, 30, 30, 1);
    setLargeSpriteControl(1, 64, 64, 0, 0, 0);
    setLargeSpriteControl(2, 64, 64, 0, 0, 0);
    setBackgroundDataImage(0, bird_background_img);
    
    setLargeSpriteDataImage(0, bird_img_0);
    setLargeSpriteDataImage(1, bird_img_1);
    setLargeSpriteDataImage(2, bird_img_2);

}