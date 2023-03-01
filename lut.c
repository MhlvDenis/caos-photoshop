#include "pic.h"

int Clamp(int X, int A, int B) {
    if (X < A) {
        return A;
    }
    if (X > B) {
        return B;
    }
    return X;
}

void LUTSetCopy(byte *LUT) {
    for (int i = 0; i < COLORS_IN_BYTE; ++i) {
        LUT[i] = i;
    }
}

void LUTSetNegative(byte *LUT) {
    for (int i = 0; i < COLORS_IN_BYTE; ++i)
        LUT[i] = COLORS_IN_BYTE - i - 1;
}

void LUTSetBrightness(byte *LUT, int Di) {
    for (int i = 0; i < COLORS_IN_BYTE; ++i) {
        LUT[i] = Clamp(i + Di, 0, COLORS_IN_BYTE - 1);
    }
}

void LUTSetContrast(byte *LUT, int A, int B) {
    for (int i = 0; i < COLORS_IN_BYTE; ++i) {
        LUT[i] = Clamp((COLORS_IN_BYTE - 1) * (i - A) / (B - A), 0,
                       (COLORS_IN_BYTE - 1));
    }
}

void LUTSetGamma(byte *LUT, double Gamma) {
    for (int i = 0; i < COLORS_IN_BYTE; ++i) {
        LUT[i] = Clamp((COLORS_IN_BYTE - 1) *
                           pow(i * 1.0 / (COLORS_IN_BYTE - 1), 1 / Gamma),
                       0, (COLORS_IN_BYTE - 1));
    }
}

void LUTSetPoster(byte *LUT, int Levels) {
}

void LUTAutoContrast(byte *LUT, PIC *P) {
    int A = COLORS_IN_BYTE;
    int B = 0;

    for (int y = 0; y < P->height; ++y) {
        for (int x = 0; x < P->width; ++x) {
            for (int c = 0; c < 3; ++c) {
                if (P->Pixels[x + y * P->width][c] < A) {
                    A = P->Pixels[x + y * P->width][c];
                }
                if (P->Pixels[x + y * P->width][c] > B) {
                    B = P->Pixels[x + y * P->width][c];
                }
            }
        }
    }
    LUTSetContrast(LUT, A, B);
}

void LUTApply(PIC *PDest, PIC *PSrc, byte *LUT) {
    for (int y = 0; y < PSrc->height; ++y) {
        for (int x = 0; x < PSrc->width; ++x) {
            for (int c = 0; c < NUM_BASE_COLORS; ++c) {
                PDest->Pixels[x + y * PDest->width][c] =
                    LUT[PSrc->Pixels[x + y * PSrc->width][c]];
            }
        }
    }
}