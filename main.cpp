#include "ObjLoad.h"
#include <windows.h>
#include <gl/glut.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

ObjLoad *objLoad = NULL;

void ShowAsix()
{
/*    glBegin(GL_LINES);*/
    //glColor3f(0.0, 1.0, 0.0);
    //glVertex3f(0,0,0);
    //glVertex3f(0,1,0);
    /*glEnd();*/

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
    /// 设置显示方式
    /// GLUT_RGB表示使用RGB颜色，与之对应的还有GLUT_INDEX（表示使用索引颜色）。
    /// GLUT_SINGLE表示使用单缓冲，与之对应的还有GLUT_DOUBLE（使用双缓冲）。
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
     //background
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(1.0f,1.0f,1.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the color of object
	glEnable(GL_COLOR_MATERIAL);
 	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    //视点
 //   glMatrixMode( GL_MODELVIEW );
  //  glLoadIdentity();
    gluLookAt(0.3,0.3,0.3, 0.0,0.0,0.0, 0,1.0,0);

    GLfloat light_ambient[] = {2.0f, 2.0f, 2.0f, 1.0f}; // 环境光
    GLfloat light_position[] = {5.0f, 10.0f, 15.0f, 0.0f}; // 光源位置
    GLfloat mat_diffuse[] = {0.3f, 0.3f, 0.3f, 1.0f}; // 漫反射
    GLfloat mat_specular[] = {0.15f, 0.15f, 0.15f, 1.0f}; // 镜面反射，控制高光
    GLfloat mat_shininess[] = {4.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

    GLfloat x, y, z;
    objLoad->updateFaceNormal();
    glColor3f(0.2, 0.2, 1.0);

    for (int i = 0;i < objLoad->numFace;i++)
    {
        glBegin(GL_TRIANGLES);

        glNormal3f(objLoad->faceNormal[i][0],objLoad->faceNormal[i][1],objLoad->faceNormal[i][2]);
        for(int j = 0;j < 3;j++)
        {
            x = 1.0 * (objLoad->vertices[objLoad->face[i][j]][0]) * 0.4;
            y = 1.0 * (objLoad->vertices[objLoad->face[i][j]][1]) * 0.4;
            z = 1.0 * (objLoad->vertices[objLoad->face[i][j]][2]) * 0.4;
            glVertex3f(x, y, z);
        }
        glEnd();
    }
    glFlush();
    ShowAsix();
    glFlush();

}

void draw()
{
    if(NULL == objLoad){
        cout << "error" << endl;
        return ;
    }

//创建窗口
    glutInitWindowPosition( 100, 100 );
    glutInitWindowSize( 400, 400 );
    glutCreateWindow( "chainhelen" );

    glutDisplayFunc( &Display);
    glutMainLoop();
}


int main(int argc, char* argv[])
{
    if(argc <= 1){
        cout << "Thers is no input" << endl;
        return 0;
    }
    string address(argv[1]);

    objLoad = new ObjLoad();
    objLoad->readFile(address);

    draw();

    delete objLoad;
    objLoad = NULL;
    return 0;
}
