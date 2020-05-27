// Load image using the stb_image library, convert the image to gray and sepia, write it back to disk
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"

int main(int argc, char *argv[]) {
    int width, height, channels;
	FILE *fp;
    unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 0);
    if(img == NULL) {
        printf("Error in loading the image %s\n",argv[1]);
        exit(1);
    }
    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

    // Convert the input image to gray
    size_t img_size = width * height * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * height * gray_channels;
	
	char img_array[width][height];
	
	for(int j=0;j<height;j++){
		for(int i=0;i<width;i++){
			unsigned char *pixelOffset = img + (i + width * j) * channels;
			img_array[i][j] = ((pixelOffset[0] + pixelOffset[1] + pixelOffset[2])/3.0)>128 ? 0 : 1;
			printf("%d", img_array[i][j] );
		}
		printf("\n");
	}
	
	fp = fopen("result.txt", "w+");
	
	for(int j=0;j<height;j+=4){
		for(int i=0;i<width;i+=2){
			unsigned char a= 
			img_array[i+1][j+3] * 0x01 +
			img_array[i][j+3] * 0x02 +
			img_array[i+1][j+2] * 0x04 +
			img_array[i][j+2] * 0x08 +
			img_array[i+1][j+1] * 0x10 +
			img_array[i][j+1] * 0x20 +
			img_array[i+1][j] * 0x40 +
			img_array[i][j] * 0x80 ;
			if(a<0x10)
			{
				fprintf(fp, "0x0%X, ", a);
			} else
			{
				fprintf(fp, "0x%X, ", a);
			}
		}
		fprintf(fp,"\n");
	}
	
	fclose(fp);

    unsigned char *gray_img = malloc(gray_img_size);
    if(gray_img == NULL) {
        printf("Unable to allocate memory for the gray image.\n");
        exit(1);
    }

    for(unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels) {
        *pg = (uint8_t)(((*p + *(p + 1) + *(p + 2))/3.0)>128 ? 255 : 0);
        if(channels == 4) {
            *(pg + 1) = *(p + 3);
        }
    }

    stbi_write_png("result.png", width, height, gray_channels, gray_img, width * gray_channels);

    stbi_image_free(img);
    free(gray_img);
}

