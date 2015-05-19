#include "ObjLoad.h"
#include <cmath>

using namespace std;

ObjLoad::ObjLoad(){
    numVertices = 0;
    numFace = 0;
    face = NULL;
    vertices = NULL;
    verNormal = NULL;
    faceNormal = NULL;
}

ObjLoad::~ObjLoad(){
    if(face){
        for(int i = 0;i < numFace;i++){
            delete []face[i];
            face[i] = NULL;
        }
        delete []face;
        face = NULL;
    }
    if(vertices){
        for(int i = 0; i < numVertices;i++){
            delete []vertices[i];
            vertices[i] = NULL;
        }
        delete []vertices;
        vertices = NULL;
    }
    if(verNormal){
        for(int i = 0;i < numVertices;i++){
            delete []verNormal[i];
            verNormal[i] = NULL;
        }
        delete []verNormal;
        verNormal = NULL;
    }
    if(faceNormal){
        for(int i = 0;i < numFace;i++){
            delete []faceNormal[i];
            faceNormal[i] = NULL;
        }
        delete []faceNormal;
        faceNormal = NULL;
    }
    numFace = 0;
    numVertices = 0;
}

void ObjLoad::readFile(string addrstr){
    int i;
    vector<double>verVector;
    vector<int>faceIndex;
    GLfloat x, y, z;

    ifstream infile(addrstr.c_str());
    string sline, s1;//每一行
    int ii=0,jj=0,kk=0;

    while(getline(infile,sline))
    {
        if(sline[0]=='v')
        {
            if(sline[1]=='n')//vn
            {
            }
            else//v
            {
                istringstream sin(sline);
                sin >> s1>> x >> y >> z;
                verVector.push_back(x);
                verVector.push_back(y);
                verVector.push_back(z);

                jj++;
            }
        }
        if (sline[0]=='f') //读取面
        {
            istringstream in(sline);
            int a;

            in>>s1;//去掉前缀f
            int i,k;

            for(i=0;i<3;i++)
            {
                in>>s1;
                //取得顶点索引和法线索引
                a=0;
                for(int j = 0;j < (int)s1.length();j++)
                {
                    a=a*10+(s1[j]-'0');
                }
                faceIndex.push_back(a - 1);
            }
            kk++;
        }
    }
    numVertices = verVector.size() / 3;
    numFace = faceIndex.size() / 3;

    vertices = new GLfloat*[numVertices];
    for(int i = 0;i < numVertices;i++){
        vertices[i] = new GLfloat[3];
    }

    face = new int*[numFace];
    for(int i = 0;i < numFace;i++){
        face[i] = new int[3];
    }

    for(int i = 0;i < numVertices;i++){
        for(int j = 0;j < 3;j++){
            vertices[i][j] = verVector[3 * i + j];
        }
    }
    for(int i = 0;i < numFace;i++){
        for(int j = 0;j < 3;j++){
            face[i][j] = faceIndex[3 * i + j];
        }
    }
    vector<double>().swap(verVector);
    vector<int>().swap(faceIndex);
}
void ObjLoad::updateVerNormal(){
    if(NULL == verNormal){
        verNormal = new GLfloat *[numVertices];
        for(int i = 0;i < numVertices;i++){
            verNormal[i] = new GLfloat[3];
        }
    }
}
void ObjLoad::updateFaceNormal(){
    if(NULL == faceNormal){
        faceNormal = new GLfloat *[numFace];
        for(int i = 0;i < numFace;i++){
            faceNormal[i] = new GLfloat[3];
        }
    }
}
void ObjLoad::deleteVerNormal(){
    if(NULL != verNormal){
        for(int i = 0;i < numVertices;i++){
            delete []verNormal[i];
            verNormal[i] = NULL;
        }
        delete []verNormal;
        verNormal = NULL;
    }
}
void ObjLoad::deleteFaceNormal(){
    if(NULL != faceNormal){
        for(int i = 0;i < numFace;i++){
            delete []faceNormal[i];
            faceNormal[i] = NULL;
        }
        delete []faceNormal;
        faceNormal = NULL;
    }
}

GLfloat ObjLoad::getAreaByFaceIndex(int findex){
    GLfloat u[3], v[3], normal[3];
    int a = face[findex][0];
    int b = face[findex][1];
    int c = face[findex][2];

    for(int i = 0;i < 3;i++){
        u[i] = vertices[b][i] - vertices[a][i];
    }
    for(int i = 0;i < 3;i++){
        v[i] = vertices[c][i] - vertices[a][i];
    }

    normal[0] = u[1] * v[2] - u[2] * v[1];
    normal[1] = u[2] * v[0] - u[0] * v[2];
    normal[2] = u[0] * v[1] - u[1] * v[0];
}

void ObjLoad::getFaceNormalByFaceIndex(GLfloat *normal,int findex){
    GLfloat u[3], v[3];
    int a = face[findex][0];
    int b = face[findex][1];
    int c = face[findex][2];

    for(int i = 0;i < 3;i++){
        u[i] = vertices[b][i] - vertices[a][i];
    }
    for(int i = 0;i < 3;i++){
        v[i] = vertices[c][i] - vertices[a][i];
    }

    normal[0] = u[1] * v[2] - u[2] * v[1];
    normal[1] = u[2] * v[0] - u[0] * v[2];
    normal[2] = u[0] * v[1] - u[1] * v[0];

    GLfloat sum = 0;
    for(int i = 0;i < 3;i++){
        sum += normal[i] * normal[i];
    }
    sum = sqrt(sum);
    sum = sum < 1e-3 ? 1e-3 : sum;
    for(int i = 0;i < 3;i++){
        normal[i] /= sum;
    }
}
