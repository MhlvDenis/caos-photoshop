#include "pic.h"

void PicDraw(PIC *P, int X0, int Y0) {
    int offset = 0;

    for (int y = 0; y < P->height; ++y) {
        for (int x = 0; x < P->width; ++x, ++offset) {
            PutPixel(X0 + x, Y0 + y, P->Pixels[offset][2], P->Pixels[offset][1],
                     P->Pixels[offset][0]);
        }
    }
}

int PicCreate(PIC *P, int NewWidth, int NewHeight) {
    P->Pixels = malloc(NewWidth * NewHeight * sizeof(RGB));
    if (P->Pixels == NULL) {
        return 0;
    }

    P->width = NewWidth;
    P->height = NewHeight;
    return 1;
}

int PicGet(PIC *P, int X, int Y, int C) {
    X = (X + P->width) % P->width;
    Y = (Y + P->height) % P->height;

    return P->Pixels[X + Y * P->width][C];
}

int PicLoad(PIC *P, char *FileName) {
    FILE *F;
    short width, height;

    P->width = P->height = 0;
    P->Pixels = NULL;

    if ((F = fopen(FileName, "rb")) == NULL) {
        return 0;
    }

    fread(&width, 2, 1, F);
    fread(&height, 2, 1, F);
    if (!PicCreate(P, width, height)) {
        fclose(F);
        return 0;
    }

    fread(P->Pixels, sizeof(RGB), width * height, F);
    fclose(F);
    return 1;
}

void PicFree(PIC *P) {
    if (P->Pixels != NULL) {
        free(P->Pixels);
    }
    P->width = P->height = 0;
    P->Pixels = NULL;
}

int PicSave(PIC *P, char *FileName) {
    FILE *F;

    if ((F = fopen(FileName, "wb")) == NULL) {
        return 0;
    }

    fwrite(&P->width, 2, 1, F);
    fwrite(&P->height, 2, 1, F);
    fwrite(P->Pixels, 3, P->width * P->height, F);

    fclose(F);
    return 1;
}
