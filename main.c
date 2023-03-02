#include <GL/gl.h>
#include <GL/glut.h>

#include "pic.h"

enum {
    FRAME_W = 800,
    FRAME_H = 600,
    MAX_FILENAME_LEN = 300,
};

enum MenuItems {
    EXIT,
    PIC_LOAD,
    PIC_SAVE,

    LUT_NEGATIVE,
    LUT_CONTRAST_50_205,
    LUT_CONTRAST_M50_255,
    LUT_GAMMA_0P5,
    LUT_GAMMA_2P4,
    LUT_AUTO_CONTRAST,
};

unsigned char Frame[FRAME_H][FRAME_W][NUM_BASE_COLORS];
float GlZoom = 2;

void PutPixel(int x, int y, int r, int g, int b) {
    if (x < 0 || y < 0 || x > FRAME_W || y > FRAME_H) {
        return;
    }
    Frame[y][x][0] = b;
    Frame[y][x][1] = g;
    Frame[y][x][2] = r;
}

void MenuHandle(int value) {
    static PIC workingPic, newlyProcessedPic;
    PIC tmpPic;
    byte lut[COLORS_IN_BYTE];

    // See resources folder for sample files.
    char sourceFilename[MAX_FILENAME_LEN] = "ape.g24\0";
    char destFilename[MAX_FILENAME_LEN] = "ape_modified.g24\0";

    switch (value) {
    // Main options
    case EXIT:
        exit(0);
    case PIC_LOAD:
        PicFree(&workingPic);
        PicFree(&newlyProcessedPic);
        if (PicLoad(&newlyProcessedPic, sourceFilename)) {
            PicCreate(&workingPic, newlyProcessedPic.width,
                      newlyProcessedPic.height);
        }
        break;
    case PIC_SAVE:
        PicSave(&newlyProcessedPic, destFilename);
        break;

    // LUT options
    case LUT_NEGATIVE:
        LUTSetNegative(lut);
        LUTApply(&newlyProcessedPic, &workingPic, lut);
        break;
    case LUT_CONTRAST_50_205:
        LUTSetContrast(lut, 50, 205);
        LUTApply(&newlyProcessedPic, &workingPic, lut);
        break;
    case LUT_CONTRAST_M50_255:
        LUTSetContrast(lut, -50, 255);
        LUTApply(&newlyProcessedPic, &workingPic, lut);
        break;
    case LUT_GAMMA_0P5:
        LUTSetGamma(lut, 0.5);
        LUTApply(&newlyProcessedPic, &workingPic, lut);
        break;
    case LUT_GAMMA_2P4:
        LUTSetGamma(lut, 2.4);
        LUTApply(&newlyProcessedPic, &workingPic, lut);
        break;
    case LUT_AUTO_CONTRAST:
        LUTAutoContrast(lut, &workingPic);
        LUTApply(&newlyProcessedPic, &workingPic, lut);
        break;
    }

    tmpPic = workingPic;
    workingPic = newlyProcessedPic;
    newlyProcessedPic = tmpPic;
    PicDraw(&workingPic, 0, 0);
}

void Display(void) {
    // Set default color for GL display.
    glClearColor(0.3, 0.5, 0.7, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2d(-1, 1);
    glPixelZoom(GlZoom, -GlZoom);
    glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

    glFinish();
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    int menu;
    int lutMenu;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(FRAME_W, FRAME_H);
    glutCreateWindow("Photoshop");

    lutMenu = glutCreateMenu(MenuHandle);
    glutSetMenu(lutMenu);
    glutAddMenuEntry("Negative", LUT_NEGATIVE);
    glutAddMenuEntry("Contrast 50...205", LUT_CONTRAST_50_205);
    glutAddMenuEntry("Contrast -50...255", LUT_CONTRAST_M50_255);
    glutAddMenuEntry("Gamma 0.5", LUT_GAMMA_0P5);
    glutAddMenuEntry("Gamma 2.4", LUT_GAMMA_2P4);
    glutAddMenuEntry("Auto contrast", LUT_AUTO_CONTRAST);

    menu = glutCreateMenu(MenuHandle);
    glutSetMenu(menu);
    glutAddMenuEntry("Open Image File", PIC_LOAD);
    glutAddMenuEntry("Save Image File", PIC_SAVE);
    glutAddSubMenu("Look-Up-Tables", lutMenu);
    glutAddMenuEntry("Exit", EXIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(Display);

    glutMainLoop();
}