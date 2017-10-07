#include <iostream>
#include <GL/glut.h>

using namespace std;

GLsizei winWidth = 420, winHeight = 420;
GLfloat red = 1.0, green = 1.0, blue = 1.0;

GLenum fillMode = GL_SMOOTH;
int xc = 320, yc = 240;

void init(void){
    glClearColor(0.6,0.6,0.6,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,300.0,0.0,300.0);
}

void displayTriangle(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glShadeModel(fillMode);
    glColor3f(red,green,blue);

    glBegin(GL_TRIANGLES);
    glVertex2i(280,20);
    glVertex2i(160,280);
    glColor3f(red,green,blue);
    glVertex2i(20,100);
    glEnd();
}

void plot_point(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(xc+x, yc+y);
    glVertex2i(xc+x, yc-y);
    glVertex2i(xc+y, yc+x);
    glVertex2i(xc+y, yc-x);
    glVertex2i(xc-x, yc-y);
    glVertex2i(xc-y, yc-x);
    glVertex2i(xc-x, yc+y);
    glVertex2i(xc-y, yc+x);
    glEnd();
}

void bresenham_circle(int r)
{
    int x=0,y=r;
    float pk=(5.0/4.0)-r;

    /* Plot the points */
    /* Plot the first point */
    plot_point(x,y);
    int k;
    /* Find all vertices till x=y */
    while(x < y)
    {
        x = x + 1;
        if(pk < 0)
            pk = pk + 2*x+1;
        else
        {
            y = y - 1;
            pk = pk + 2*(x - y) + 1;
        }
        plot_point(x,y);
    }
    glFlush();
}


void fillOption(GLint selectedOption){
    cout<<selectedOption<<endl;
    switch (selectedOption){
        case 1:
            displayTriangle();
            break;
        case 2:
            fillMode = GL_SMOOTH;
            break;
        case 3:
            bresenham_circle(1);
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(winWidth,winHeight);
    glutCreateWindow("Menu");

    init();
    glutDisplayFunc(displayTriangle);
    glutCreateMenu(fillOption);
    glutAddMenuEntry("Draw Triangle",1);
    glutAddMenuEntry("Draw Circle",2);
    glutAddMenuEntry("Draw Square",3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}