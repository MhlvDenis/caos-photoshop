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
    RGB *Pixels;
} PIC;

void PutPixel(int X, int Y, int R, int G, int B);

void PicDraw(PIC *P, int X0, int Y0);
int PicCreate(PIC *P, int NewWidth, int NewHeight);
int PicGet(PIC *P, int X, int Y, int C);
int PicLoad(PIC *P, char *FileName);
void PicFree(PIC *P);
int PicSave(PIC *P, char *FileName);

int Clamp(int X, int A, int B);

void LUTSetCopy(byte *LUT);
void LUTSetNegative(byte *LUT);
void LUTSetBrightness(byte *LUT, int Di);
void LUTSetContrast(byte *LUT, int A, int B);
void LUTSetGamma(byte *LUT, double Gamma);
void LUTAutoContrast(byte *LUT, PIC *P);

void LUTApply(PIC *PDest, PIC *PSrc, byte *LUT);