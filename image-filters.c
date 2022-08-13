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
int write_ppm_color_bitmap(char *filename, PPM_Image_Buffer *buf);

int main() {
    PPM_Image_Buffer* buf = malloc(sizeof(PPM_Image_Buffer));

    read_ppm_color_bitmap("bird.ppm", buf);
    write_ppm_color_bitmap("bird2.ppm", buf);
    free(buf->data);
    free(buf);
    return 0;
}

int read_ppm_color_bitmap(char* filename, PPM_Image_Buffer* buf){
    
    FILE *f = fopen(filename, "r");
    if (!f){
        perror("fopen");
        return -1;
    }
    char m_num[3];
    fgets(m_num, 3, f);
    if (strcmp(m_num, "P3")){
        fprintf(stderr, "Invalid format\n");
        return -1;
    }
    int row, col;
    fscanf(f, "%d %d", &row, &col);
    buf->coln = col;
    buf->rown = row;
    buf->data = malloc(row * col * sizeof(Pixel_Data));
    
    int arr[row * col * 3]; 
    int curr_num;
    int arrC = 0; 
    for (;fscanf(f, "%hhu %hhu %hhu", &(buf->data[arrC].red), &(buf->data[arrC].green), &(buf->data[arrC].blue)) != EOF; arrC++) {
        
        if (buf->data[arrC].red > 255  || buf->data[arrC].green > 255 || buf->data[arrC].blue > 255){
            fprintf(stderr, "Invalid format\n");
            return -1;
        }
    }  

    fclose(f);  
    return 0;
}