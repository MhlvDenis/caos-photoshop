#include "pic.h"

int Clamp(int x, int left, int right) {
    if (x < left) {
        return left;
    }
    if (x > right) {
        return right;
    }
    return x;
}

void LUTSetCopy(byte *lut) {
    for (int i = 0; i < COLORS_IN_BYTE; ++i) {
        lut[i] = i;
    }
}

void LUTSetNegative(byte *lut) {
    for (int i = 0; i < COLORS_IN_BYTE; ++i) {
        lut[i] = COLORS_IN_BYTE - i - 1;
    }
}

void LUTSetBrightness(byte *lut, int di) {
    for (int i = 0; i < COLORS_IN_BYTE; ++i) {
        lut[i] = Clamp(i + di, 0, COLORS_IN_BYTE - 1);
    }
}

void LUTSetContrast(byte *lut, int left, int right) {
    for (int i = 0; i < COLORS_IN_BYTE; ++i) {
        lut[i] = Clamp((COLORS_IN_BYTE - 1) * (i - left) / (right - left), 0,
                       (COLORS_IN_BYTE - 1));
    }
}

void LUTSetGamma(byte *lut, double gamma) {
    for (int i = 0; i < COLORS_IN_BYTE; ++i) {
        lut[i] = Clamp((COLORS_IN_BYTE - 1) *
                           pow(i * 1.0 / (COLORS_IN_BYTE - 1), 1 / gamma),
                       0, (COLORS_IN_BYTE - 1));
    }
}

void LUTAutoContrast(byte *lut, PIC *pic) {
    int left = COLORS_IN_BYTE;
    int right = 0;

    for (int y = 0; y < pic->height; ++y) {
        for (int x = 0; x < pic->width; ++x) {
            for (int c = 0; c < 3; ++c) {
                if (pic->pixels[x + y * pic->width][c] < left) {
                    left = pic->pixels[x + y * pic->width][c];
                }
                if (pic->pixels[x + y * pic->width][c] > right) {
                    right = pic->pixels[x + y * pic->width][c];
                }
            }
        }
    }
    LUTSetContrast(lut, left, right);
}

void LUTApply(PIC *picDest, PIC *picSrc, const byte *lut) {
    for (int y = 0; y < picSrc->height; ++y) {
        for (int x = 0; x < picSrc->width; ++x) {
            for (int c = 0; c < NUM_BASE_COLORS; ++c) {
                picDest->pixels[x + y * picDest->width][c] =
                    lut[picSrc->pixels[x + y * picSrc->width][c]];
            }
        }
    }
}
