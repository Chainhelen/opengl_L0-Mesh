#ifndef OBJLOAD_H
#define OBJLOAD_H

#include <windows.h>
#include <gl/glut.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class ObjLoad{
    public:
        int numVertices;
        int numFace;

        int **face;
        GLfloat **vertices;
        GLfloat **verNormal;
        GLfloat **faceNormal;

    public:
        void readFile(string filename);
        void updateVerNormal();
        void updateFaceNormal();
        void deleteVerNormal();
        void deleteFaceNormal();
        GLfloat getAreaByFaceIndex(int findex);
        void getFaceNormalByFaceIndex(GLfloat *normal,int findex);

        ObjLoad();
        ~ObjLoad();
};
#endif
