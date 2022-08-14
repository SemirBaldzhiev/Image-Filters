#include "image_filters.h"

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
    
    //int arr[row * col * 3]; 
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
    return !!(mask & (1ULL << bit));
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

int write_ppm_color_bitmap_binary(char *filename, PPM_Image_Buffer *buf) {
    FILE *f = fopen(filename, "wb");

    if(!f){
        perror("fopen");
        return -1;
    }

    char header[200];
    sprintf(header, "P6\n%d %d\n255\n", buf->rown, buf->coln);
    fwrite(header, 1, strlen(header), f);

    fwrite(buf->data, sizeof(Pixel_Data), buf->rown * buf->coln, f);

    return 0;
}