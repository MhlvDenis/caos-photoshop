#include "pic.h"

void PicDraw(PIC *pic, int x0, int y0) {
    int offset = 0;

    for (int y = 0; y < pic->height; ++y) {
        for (int x = 0; x < pic->width; ++x, ++offset) {
            PutPixel(x0 + x, y0 + y, pic->pixels[offset][2],
                     pic->pixels[offset][1], pic->pixels[offset][0]);
        }
    }
}

int PicCreate(PIC *pic, int newWidth, int newHeight) {
    pic->pixels = malloc(newWidth * newHeight * sizeof(RGB));
    if (pic->pixels == NULL) {
        return 0;
    }

    pic->width = newWidth;
    pic->height = newHeight;
    return 1;
}

int PicGet(PIC *pic, int x, int y, int color) {
    x = (x + pic->width) % pic->width;
    y = (y + pic->height) % pic->height;

    return pic->pixels[x + y * pic->width][color];
}

int PicLoad(PIC *pic, char *filename) {
    FILE *file;
    short width, height;

    pic->width = pic->height = 0;
    pic->pixels = NULL;

    if ((file = fopen(filename, "rb")) == NULL) {
        return 0;
    }

    fread(&width, 2, 1, file);
    fread(&height, 2, 1, file);
    if (!PicCreate(pic, width, height)) {
        fclose(file);
        return 0;
    }

    fread(pic->pixels, sizeof(RGB), width * height, file);
    fclose(file);
    return 1;
}

void PicFree(PIC *pic) {
    if (pic->pixels != NULL) {
        free(pic->pixels);
    }
    pic->width = pic->height = 0;
    pic->pixels = NULL;
}

int PicSave(PIC *pic, char *filename) {
    FILE *file;

    if ((file = fopen(filename, "wb")) == NULL) {
        return 0;
    }

    fwrite(&pic->width, 2, 1, file);
    fwrite(&pic->height, 2, 1, file);
    fwrite(pic->pixels, 3, pic->width * pic->height, file);

    fclose(file);
    return 1;
}
