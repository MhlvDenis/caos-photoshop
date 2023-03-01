#include <GL/gl.h>
#include <GL/glut.h>

#include "pic.h"

enum {
    FRAME_W = 800,
    FRAME_H = 600,
    MAX_FILENAME_LEN = 300,
};

unsigned char Frame[FRAME_H][FRAME_W][NUM_BASE_COLORS];
float GL_ZOOM = 2;

void PutPixel(int X, int Y, int R, int G, int B) {
    if (X < 0 || Y < 0 || X > FRAME_W || Y > FRAME_H) {
        return;
    }
    Frame[Y][X][0] = B;
    Frame[Y][X][1] = G;
    Frame[Y][X][2] = R;
}

void MenuHandle(int value) {
    static PIC working_pic, newly_processed_pic;
    PIC tmp;
    byte LUT[COLORS_IN_BYTE];

    // See resources folder for sample files.
    char source_filename[MAX_FILENAME_LEN] = "ape.g24\0";
    char dest_filename[MAX_FILENAME_LEN] = "ape_modified.g24\0";

    switch (value) {
        case 0:
            exit(0);
        case 1:
            PicFree(&working_pic);
            PicFree(&newly_processed_pic);
            if (PicLoad(&newly_processed_pic, source_filename)) {
                PicCreate(&working_pic, newly_processed_pic.width,
                          newly_processed_pic.height);
            }
            break;
        case 2:
            PicSave(&newly_processed_pic, dest_filename);
            break;
        default:
            switch (value) {
            case 10:
                LUTSetNegative(LUT);
                break;
            case 11:
                // You are free to set your own LUT transform params.
                LUTSetContrast(LUT, 50, 205);
                break;
            case 12:
                LUTSetContrast(LUT, -50, 255);
                break;
            case 13:
                LUTSetGamma(LUT, 0.5);
                break;
            case 14:
                LUTSetGamma(LUT, 2.4);
                break;
            }
            LUTApply(&newly_processed_pic, &working_pic, LUT);
            break;
    }

    tmp = working_pic;
    working_pic = newly_processed_pic;
    newly_processed_pic = tmp;
    PicDraw(&working_pic, 0, 0);
}

void Display(void) {
    // Set default color for GL display.
    glClearColor(0.3, 0.5, 0.7, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2d(-1, 1);
    glPixelZoom(GL_ZOOM, -GL_ZOOM);
    glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

    glFinish();
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    int menu;
    int lut_menu;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(FRAME_W, FRAME_H);
    glutCreateWindow("Photoshop");

    lut_menu = glutCreateMenu(MenuHandle);
    glutSetMenu(lut_menu);
    glutAddMenuEntry("Negative", 10);
    glutAddMenuEntry("Contrast 50...205", 11);
    glutAddMenuEntry("Contrast -50...255", 12);
    glutAddMenuEntry("Gamma 0.5", 13);
    glutAddMenuEntry("Gamma 2.4", 14);

    menu = glutCreateMenu(MenuHandle);
    glutSetMenu(menu);
    glutAddMenuEntry("Open Image File", 1);
    glutAddMenuEntry("Save Image File", 2);
    glutAddSubMenu("Look-Up-Tables", lut_menu);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(Display);

    glutMainLoop();
}