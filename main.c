#include <getopt.h>
#include "image_filters.h"

int main(int argc, char **argv) {
    PPM_Image_Buffer* buf = malloc(sizeof(PPM_Image_Buffer));
    if (read_ppm_color_bitmap(argv[1], buf)) {
        perror("read image");
        return EXIT_FAILURE;
    }
    int opt;

    if ((opt = getopt(argc, argv, "f:gbt")) != -1){
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
            case 'b':
                read_ppm_color_bitmap(argv[1], buf);
                if(write_ppm_color_bitmap_binary(argv[2], buf)){
                    perror("write binary");
                    return EXIT_FAILURE;
                }
                break;
            case 't':

                if(write_ppm_color_bitmap(argv[2], buf)){
                    perror("write binary");
                    return EXIT_FAILURE;
                }
                break;
        }
    }
    if(write_ppm_color_bitmap_binary(argv[2], buf)){
        perror("write image");
        return EXIT_FAILURE;
    }
    free(buf->data);
    free(buf);
    return 0;
}



