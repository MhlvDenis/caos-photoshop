#include <GL/gl.h>
#include <GL/glut.h>

#include "pic.h"

enum {
    FRAME_W = 800,
    FRAME_H = 600,
    MAX_FILENAME_LEN = 300,
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
    case 0:
        exit(0);
    case 1:
        PicFree(&workingPic);
        PicFree(&newlyProcessedPic);
        if (PicLoad(&newlyProcessedPic, sourceFilename)) {
            PicCreate(&workingPic, newlyProcessedPic.width,
                      newlyProcessedPic.height);
        }
        break;
    case 2:
        PicSave(&newlyProcessedPic, destFilename);
        break;
    default:
        switch (value) {
        case 10:
            LUTSetNegative(lut);
            break;
        case 11:
            // You are free to set your own lut transform params.
            LUTSetContrast(lut, 50, 205);
            break;
        case 12:
            LUTSetContrast(lut, -50, 255);
            break;
        case 13:
            LUTSetGamma(lut, 0.5);
            break;
        case 14:
            LUTSetGamma(lut, 2.4);
            break;
        }
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
    glutAddMenuEntry("Negative", 10);
    glutAddMenuEntry("Contrast 50...205", 11);
    glutAddMenuEntry("Contrast -50...255", 12);
    glutAddMenuEntry("Gamma 0.5", 13);
    glutAddMenuEntry("Gamma 2.4", 14);

    menu = glutCreateMenu(MenuHandle);
    glutSetMenu(menu);
    glutAddMenuEntry("Open Image File", 1);
    glutAddMenuEntry("Save Image File", 2);
    glutAddSubMenu("Look-Up-Tables", lutMenu);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(Display);

    glutMainLoop();
}