#include <GL/gl.h>
#include <GL/glut.h>

#include "pic.h"

#define FRAME_W 800
#define FRAME_H 600
unsigned char Frame[FRAME_H][FRAME_W][3];
double Zoom = 2;

void PutPixel(int X, int Y, int R, int G, int B) {
    if (X < 0 || Y < 0 || X > FRAME_W || Y > FRAME_H)
        return;

    Frame[Y][X][0] = B;
    Frame[Y][X][1] = G;
    Frame[Y][X][2] = R;
}

void MenuHandle(int value) {
    static PIC pic;
    char source_filename[300] = "ape.g24\0";
    char dest_filename[300] = "ape_modified.g24\0";

    switch (value) {
        case 0:
            exit(0);
            break;
        case 1:
            PicFree(&pic);
            PicLoad(&pic, source_filename);
            break;
        case 2:
            PicSave(&pic, dest_filename);
            break;
    }
    
    PicDraw(&pic, 0, 0);
}

void Display(void) {
    glClearColor(0.3, 0.5, 0.7, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2d(-1, 1);
    glPixelZoom(Zoom, -Zoom);
    glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

    glFinish();
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    int menu;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(FRAME_W, FRAME_H);
    glutCreateWindow("Photoshop");

    menu = glutCreateMenu(MenuHandle);
    glutSetMenu(menu);
    glutAddMenuEntry("Open Image File", 1);
    glutAddMenuEntry("Save Image File", 2);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(Display);

    glutMainLoop();
}