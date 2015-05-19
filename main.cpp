#include "ObjLoad.h"
#include <windows.h>
#include <gl/glut.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

ObjLoad *objLoad = NULL;

void ShowAsix()
{
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1);
    glEnd();
}

void Display()
{
    GLfloat x, y, z;

    for (int i = 0;i < objLoad->numFace;i++)
    {
        glBegin(GL_TRIANGLES);
        for(int j = 0;j < 3;j++)
        {
            x = 1.0 * (objLoad->vertices[objLoad->face[i][j]][0]) * 0.5;
            y = 1.0 * (objLoad->vertices[objLoad->face[i][j]][1]) * 0.5;
            z = 1.0 * (objLoad->vertices[objLoad->face[i][j]][2]) * 0.5;
            glColor3f(1.0,0.0,0.0);
            glVertex3f(x, y, z);
        }
        glEnd();
    }
    ShowAsix();
    glFlush();
}

void draw()
{
    if(NULL == objLoad){
        cout << "error" << endl;
        return ;
    }
    /// 设置显示方式
    /// GLUT_RGB表示使用RGB颜色，与之对应的还有GLUT_INDEX（表示使用索引颜色）。
    /// GLUT_SINGLE表示使用单缓冲，与之对应的还有GLUT_DOUBLE（使用双缓冲）。
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );


//创建窗口
    glutInitWindowPosition( 100, 100 );
    glutInitWindowSize( 400, 400 );
    glutCreateWindow( "chainhelen" );

    //视点
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
//    gluLookAt(0.7, 0, 1.0, 0, 0, 0, 0, 1, 0);

    //background
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(1.0f,1.0f,1.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //光源
/*    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = {1.0, 1.0, 1.0, -1};
    glLightfv(GL_LIGHTING, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHTING, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHTING, GL_POSITION,position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);*/

/*    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };*/
    //GLfloat mat_shininess[] = { 50.0 };
    //GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    //GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    //GLfloat Light_Model_Ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 }; //
    //glClearColor (0.0, 0.0, 0.0, 0.0);
    //glShadeModel (GL_SMOOTH);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    //glLightModelfv( GL_LIGHT_MODEL_AMBIENT , Light_Model_Ambient ); //
    //glEnable(GL_LIGHTING);
    /*glEnable(GL_LIGHT0);*/
//    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc( &Display);
    glutMainLoop();
}


int main(int argc, char* argv[])
{
    objLoad = new ObjLoad();
    objLoad->readFile("NoisyFandisk-Impulsive.obj");

    draw();

    delete objLoad;
    objLoad = NULL;
    return 0;
}
