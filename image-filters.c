#include <stdio.h>
#include <stdint.h>

typedef struct Pixel_Data {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Pixel_Data;

typedef struct PPM_Image_Buffer {
    Pixel_Data* data;
    int rown, coln;
} PPM_Image_Buffer;



int main() {
    return 0;
}