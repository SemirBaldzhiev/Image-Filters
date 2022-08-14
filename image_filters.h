#ifndef __IMAGE_FILTERS_H__
#define __IMAGE_FILTERS_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


typedef struct Pixel_Data {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Pixel_Data;

typedef struct PPM_Image_Buffer {
    Pixel_Data* data;
    int rown, coln;
} PPM_Image_Buffer;

int read_ppm_color_bitmap(char* filename, PPM_Image_Buffer* buf);
int read_ppm_color_bitmap_binary(char* filename, PPM_Image_Buffer* buf);
int write_ppm_color_bitmap(char *filename, PPM_Image_Buffer *buf);
int write_ppm_color_bitmap_binary(char *filename, PPM_Image_Buffer *buf);
void filter_color_component(PPM_Image_Buffer* buf, unsigned int rgb_mask);
void convert_to_grayscale(PPM_Image_Buffer* buf);
int check_bit(unsigned int mask, int bit);

#endif