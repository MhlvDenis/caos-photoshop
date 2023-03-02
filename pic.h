#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    NUM_BASE_COLORS = 3,
    COLORS_IN_BYTE = 256,
};

typedef unsigned char byte;
typedef byte RGB[NUM_BASE_COLORS];

typedef struct {
    int width, height;
    RGB *pixels;
} PIC;

void PutPixel(int x, int y, int r, int g, int b);

void PicDraw(PIC *pic, int x0, int y0);
int PicCreate(PIC *pic, int newWidth, int newHeight);
int PicGet(PIC *pic, int x, int y, int color);
int PicLoad(PIC *pic, char *filename);
void PicFree(PIC *pic);
int PicSave(PIC *pic, char *filename);

int Clamp(int x, int left, int right);

void LUTSetCopy(byte *lut);
void LUTSetNegative(byte *lut);
void LUTSetBrightness(byte *lut, int di);
void LUTSetContrast(byte *lut, int left, int right);
void LUTSetGamma(byte *lut, double gamma);
void LUTAutoContrast(byte *lut, PIC *pic);
void LUTApply(PIC *picDest, PIC *picSrc, const byte *lut);
