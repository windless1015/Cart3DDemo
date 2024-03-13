#pragma once

#include <QVector3D>
#include "common.h"

/**********
* #include <cmath>
* #include <math.h>
* 我这里的环境中,上面的两个头文件是包含M_PI的值的,
* 但是环境在移植后,便无法使用
***********/
//#define M_PI 3.14159265359  //放到common.h中了

//struct MyTraits : public OpenMesh::DefaultTraits
//{
//    HalfedgeAttributes(OpenMesh::Attributes::PrevHalfedge);
//};
//
////三角网格
//typedef OpenMesh::TriMesh_ArrayKernelT<MyTraits>  MyMesh;


/******
* radius:圆的半径
* sectorCount:圆周上的点的数量
* v3d:圆心
*****/
void createCircle(float radius, int sectorCount, QVector3D& v3d) {
    MyMesh mesh;
    
    // 创建顶点、面和半边数据结构
    MyMesh::VertexHandle center = mesh.add_vertex(MyMesh::Point(v3d[0], v3d[1], v3d[2]));
    std::vector<MyMesh::VertexHandle> sectorVertices;
    for (int i = 0; i <= sectorCount; i++)
    {
        float angle = (2 * M_PI_ / sectorCount) * i;
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);
    
        sectorVertices.push_back(mesh.add_vertex(MyMesh::Point(x, y, 0.0f)));
    }
    
    // 添加三角面片
    std::vector<MyMesh::VertexHandle> faceVertices;
    faceVertices.push_back(center);
    for (int i = 0; i <= sectorCount; i++)
        faceVertices.push_back(sectorVertices[i]);
    mesh.add_face(faceVertices);
    
    // 保存模型
    OpenMesh::IO::write_mesh(mesh, "circle.stl");
}


//eg:
//int main(int argc, char** argv)
//{
//
//
//    float radius = 0.5; //圆的半径
//    int sectorCount = 360; // 圆周上的点的数量
//    QVector3D qv3d(0.0f, 0.0f, 0.0f);
//    
//    createCircle(radius, sectorCount, qv3d);
//
//    return 0;
//}



//int main(int argc, char** argv)
//{
//    MyMesh mesh;
//
//    float radius = 0.5; //圆的半径
//    int sectorCount = 360; // 圆周上的点的数量
//
//    // 创建顶点、面和半边数据结构
//    MyMesh::VertexHandle center = mesh.add_vertex(MyMesh::Point(0.0f, 0.0f, 0.0f));
//    std::vector<MyMesh::VertexHandle> sectorVertices;
//    for (int i = 0; i <= sectorCount; i++)
//    {
//        float angle = (2 * M_PI / sectorCount) * i;
//        float x = radius * std::cos(angle);
//        float y = radius * std::sin(angle);
//
//        sectorVertices.push_back(mesh.add_vertex(MyMesh::Point(x, y, 0.0f)));
//    }
//
//    // 添加三角面片
//    std::vector<MyMesh::VertexHandle> faceVertices;
//    faceVertices.push_back(center);
//    for (int i = 0; i <= sectorCount; i++)
//        faceVertices.push_back(sectorVertices[i]);
//    mesh.add_face(faceVertices);
//
//    // 保存模型
//    OpenMesh::IO::write_mesh(mesh, "circle.obj");
//
//    return 0;
//}