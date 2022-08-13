#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

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
void filter_color_component(PPM_Image_Buffer* buf, unsigned int rgb_mask);
void convert_to_grayscale(PPM_Image_Buffer* buf);
int check_bit(unsigned int mask, int bit);

int main(int argc, char **argv) {
    PPM_Image_Buffer* buf = malloc(sizeof(PPM_Image_Buffer));
    if (read_ppm_color_bitmap(argv[1], buf)) {
        perror("read image");
        return EXIT_FAILURE;
    }
    int opt;

    if ((opt = getopt(argc, argv, "f:g")) != -1){
        switch (opt)
        {
            case 'g':
                convert_to_grayscale(buf);
                break;
            case 'f':
                if (!strcmp(optarg, "rb")){
                    filter_color_component(buf, 5);
                }
                else if (!strcmp(optarg, "gb")){
                    filter_color_component(buf, 6);
                }
                else if (!strcmp(optarg, "g")){
                    filter_color_component(buf, 2);
                }
                else if (!strcmp(optarg, "r")){
                    filter_color_component(buf, 1);
                }
                else if (!strcmp(optarg, "b")){
                    filter_color_component(buf, 4);
                }
                else if (!strcmp(optarg, "rg")){
                    filter_color_component(buf, 3);
                }
                break;
        }
    }


    //read_ppm_color_bitmap("bird.ppm", buf);
    //filter_color_component(buf, 5);
    //convert_to_grayscale(buf);
    if(write_ppm_color_bitmap(argv[2], buf)){
        perror("write image");
        return EXIT_FAILURE;
    }
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
    int row, col, max_val;
    fscanf(f, "%d %d", &row, &col);
    fscanf(f, "%d", &max_val);
    buf->coln = col;
    buf->rown = row;
    buf->data = malloc(row * col * sizeof(Pixel_Data));
    
    int arr[row * col * 3]; 
    int curr_num;
    int arrC = 0; 
    for (;fscanf(f, "%hhu %hhu %hhu", &(buf->data[arrC].red), &(buf->data[arrC].green), &(buf->data[arrC].blue)) != EOF; arrC++) {
        
        if (buf->data[arrC].red > max_val  || buf->data[arrC].green > max_val || buf->data[arrC].blue > max_val){
            fprintf(stderr, "Invalid format\n");
            return -1;
        }
    }  

    fclose(f);  
    return 0;
}

int write_ppm_color_bitmap(char *filename, PPM_Image_Buffer *buf) {
    FILE *f = fopen(filename, "w");
    if (!f){
        perror("fopen");
        return -1;
    }
    fprintf(f, "P3\n");
    fprintf(f, "%d %d\n", buf->rown, buf->coln);
    fprintf(f, "255\n");

    for (int i = 0; i < buf->rown * buf->coln; i++){
        fprintf(f, "%hhu %hhu %hhu", buf->data[i].red, buf->data[i].green, buf->data[i].blue);
        if (i != buf->coln * buf->rown - 1){
            fputc(' ', f);
        }
    }

    fclose(f);
    return 0;
}

int check_bit(unsigned int mask, int bit){
    return !!(mask & (1 << bit));
}

void filter_color_component(PPM_Image_Buffer* buf, unsigned int rgb_mask){

    int first_bit = check_bit(rgb_mask, 0);
    int second_bit = check_bit(rgb_mask, 1);
    int third_bit = check_bit(rgb_mask, 2);
    
    for (int i = 0; i < buf->rown * buf->coln; i++){
        buf->data[i].red *= first_bit;
        buf->data[i].green *= second_bit;
        buf->data[i].blue *= third_bit;
    }
}

void convert_to_grayscale(PPM_Image_Buffer* buf) {
    for (int i = 0; i < buf->rown * buf->coln; i++){
        int gray = buf->data[i].red * 0.3 + buf->data[i].green * 0.59 + buf->data[i].blue * 0.11;
        buf->data[i].red = gray;
        buf->data[i].green = gray;
        buf->data[i].blue = gray;
    }
}