#pragma once
#include "common.h"

// 包含必要的头文件
//#include <cmath>
#include <iostream>

//void createCone_cylinder(MyMesh& mesh, float radius, float height, int slices) {
//    // 清空现有网格数据
//    mesh.clear();
//
//    // 添加圆锥
//    MyMesh::VertexHandle cone = mesh.add_vertex(MyMesh::Point(0.0, 0.0, height));
//    for (int i = 0; i < slices; ++i) {
//        float theta1 = 2.0f * M_PI_ * i / slices;
//        float theta2 = 2.0f * M_PI_ * (i + 1) / slices;
//
//        float x1 = radius * std::cos(theta1);
//        float y1 = radius * std::sin(theta1);
//
//        float x2 = radius * std::cos(theta2);
//        float y2 = radius * std::sin(theta2);
//
//        MyMesh::VertexHandle v1 = mesh.add_vertex(MyMesh::Point(x1, y1, 0.0));
//        MyMesh::VertexHandle v2 = mesh.add_vertex(MyMesh::Point(x2, y2, 0.0));
//
//        // 添加侧面的矩形面
//        mesh.add_face(v1, v2, cone);
//    }
//    //在圆锥下面添加一个圆柱
//    MyMesh::VertexHandle cylinder;
//
//    //to do..
//
//}


/*******
* float radius:半径
* float height:圆锥与圆锥的高度,他们是一样的
* int slices:精细程度
****/
//createCone_cylinder2(mesh, 1.0f, 2.0f, 3000);
void createCone_cylinder2(MyMesh& mesh, float radius, float height, int slices) {
    // 清空现有网格数据
    mesh.clear();

    // 添加圆锥
    MyMesh::VertexHandle cone = mesh.add_vertex(MyMesh::Point(0.0, 0.0, height));
    MyMesh::VertexHandle cone_bottom = mesh.add_vertex(MyMesh::Point(0.0, 0.0, 0.0));
    for (int i = 0; i < slices; ++i) {
        //theta1与theta2是弧度
        float theta1 = 2.0f * M_PI_ * i / slices;
        float theta2 = 2.0f * M_PI_ * (i + 1) / slices;

        //radius是半径
        float x1 = radius * std::cos(theta1);
        float y1 = radius * std::sin(theta1);

        float x2 = radius * std::cos(theta2);
        float y2 = radius * std::sin(theta2);

        MyMesh::VertexHandle v1 = mesh.add_vertex(MyMesh::Point(x1, y1, 0.0));
        MyMesh::VertexHandle v2 = mesh.add_vertex(MyMesh::Point(x2, y2, 0.0));

        // 添加侧面的矩形面
        mesh.add_face(v1, v2, cone);
        //mesh.add_face(v1, v2, cone_bottom);
        ////圆锥封底
        mesh.add_face(cone_bottom, v2, v1);
    }
    //在圆锥下面添加一个圆柱
    MyMesh::VertexHandle cylinder = mesh.add_vertex(MyMesh::Point(0.0, 0.0, -height)); // 添加圆柱的底部中心点
    for (int i = 0; i < slices; ++i) {

        float theta1 = 2.0f * M_PI_ * i / slices;
        float theta2 = 2.0f * M_PI_ * (i + 1) / slices;

        float x1 = radius / 2 * std::cos(theta1);
        float y1 = radius / 2 * std::sin(theta1);

        float x2 = radius / 2 * std::cos(theta2);
        float y2 = radius / 2 * std::sin(theta2);

        MyMesh::VertexHandle v1 = mesh.add_vertex(MyMesh::Point(x1, y1, 0.0));
        MyMesh::VertexHandle v2 = mesh.add_vertex(MyMesh::Point(x2, y2, 0.0));
        MyMesh::VertexHandle v3 = mesh.add_vertex(MyMesh::Point(x1, y1, -height)); // 添加圆柱的底部顶点
        MyMesh::VertexHandle v4 = mesh.add_vertex(MyMesh::Point(x2, y2, -height)); // 添加圆柱的相邻顶点

        // 添加圆柱的底面的三角形面
        mesh.add_face(v4, v3, cylinder);

        //if (i == 0)
        //{

        //    float x1 = radius / 2 * std::cos(theta1);
        //    float y1 = radius / 2 * std::sin(theta1);

        //    float x2 = radius / 2 * std::cos(theta2);
        //    float y2 = radius / 2 * std::sin(theta2);

        //    mesh.add_face(v1, v3, v4);//很好,是个倒三角
        //    mesh.add_face(v1, v4, v2);
        //    continue;
        //}

        // 添加圆柱的侧面的矩形面
        //mesh.add_face(v4, v1, v3);
        mesh.add_face(v1, v3, v4);
        mesh.add_face(v1, v4, v2);
    }

}



/*******
* float radius:半径
* float height:圆锥与圆锥的高度,他们是一样的
* int slices:精细程度
****/
void create_Arrow(float radius, float  height, int slices) {
    MyMesh mesh;
    createCone_cylinder2(mesh, radius, height, slices);

    if (OpenMesh::IO::write_mesh(mesh, "arrow.stl")) {
        std::cout << "Cone mesh successfully saved to arrow.stl\n";
    }
    else {
        std::cerr << "Error saving mesh to arrow.stl\n";
    }
}

//eg:
//int main() {
//    float radius = 1.0f;
//    float height = 2.0f;
//    int slices = 300;
//    create_Arrow(radius, height, slices);
//
//    return 0;
//}

//int main() {
//    MyMesh mesh;
//    createCone_cylinder2(mesh, 1.0f, 2.0f, 300);
//
//    if (OpenMesh::IO::write_mesh(mesh, "Cone_cylinder.off")) {
//        std::cout << "Cone mesh successfully saved to Cone_cylinder.off\n";
//    }
//    else {
//        std::cerr << "Error saving mesh to Cone_cylinder.off\n";
//    }
//
//    return 0;
//}