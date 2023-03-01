#include "pic.h"

void PicDraw(PIC *P, int X0, int Y0) {
    int x, y, offset = 0;

    for (y = 0; y < P->H; ++y) {
        for (x = 0; x < P->W; ++x, ++offset) {
            PutPixel(X0 + x, Y0 + y, P->Pixels[offset][2], P->Pixels[offset][1],
                     P->Pixels[offset][0]);
        }
    }
}

int PicCreate(PIC *P, int NewW, int NewH) {
    P->Pixels = malloc(NewW * NewH * sizeof(RGB));
    if (P->Pixels == NULL) {
        return 0;
    }

    P->W = NewW;
    P->H = NewH;
    return 1;
}

int PicGet(PIC *P, int X, int Y, int C) {
    X = (X + P->W) % P->W;
    Y = (Y + P->H) % P->H;

    return P->Pixels[X + Y * P->W][C];
}

int PicLoad(PIC *P, char *FileName) {
    FILE *F;
    short w, h;

    P->W = P->H = 0;
    P->Pixels = NULL;

    if ((F = fopen(FileName, "rb")) == NULL) {
        return 0;
    }

    fread(&w, 2, 1, F);
    fread(&h, 2, 1, F);
    if (!PicCreate(P, w, h)) {
        fclose(F);
        return 0;
    }

    fread(P->Pixels, sizeof(RGB), w * h, F);
    fclose(F);
    return 1;
}

void PicFree(PIC *P) {
    if (P->Pixels != NULL) {
        free(P->Pixels);
    }
    P->W = P->H = 0;
    P->Pixels = NULL;
}

int PicSave(PIC *P, char *FileName) {
    FILE *F;

    if ((F = fopen(FileName, "wb")) == NULL) {
        return 0;
    }

    fwrite(&P->W, 2, 1, F);
    fwrite(&P->H, 2, 1, F);
    fwrite(P->Pixels, 3, P->W * P->H, F);

    fclose(F);
    return 1;
}
