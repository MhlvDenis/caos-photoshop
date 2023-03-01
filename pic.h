#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;
typedef byte RGB[3];

typedef struct {
    int W, H;
    RGB *Pixels;
} PIC;

void PutPixel(int X, int Y, int R, int G, int B);

void PicDraw(PIC *P, int X0, int Y0);
int PicCreate(PIC *P, int NewW, int NewH);
int PicGet(PIC *P, int X, int Y, int C);
int PicLoad(PIC *P, char *FileName);
void PicFree(PIC *P);
int PicSave(PIC *P, char *FileName);
