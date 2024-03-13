#pragma once

#include <iostream>

#include "common.h"




//createCompleteDonut(mesh, 1.0f, 0.3f, 100, 50);
/*
* mesh: 一个空的 MyMesh 对象，用于存储甜甜圈网格的顶点和面信息。
outerRadius: 外环的半径。
innerRadius: 内环的半径。
outerSegments: 外环的分段数，用于控制外环的平滑度。
innerSegments: 内环的分段数，用于控制内环的平滑度。
*/
//createCompleteDonut(mesh, 1.0f, 0.3f, 60, 30);
void createCompleteDonut(MyMesh& mesh, float outerRadius, float innerRadius, int outerSegments, int innerSegments) {
    // 清空现有网格数据
    mesh.clear();


    // 创建顶点和面

    // 外环的顶点
    for (int i = 0; i < outerSegments; ++i) {
        //M_PI_ 被乘以 2 是为了计算一个完整的圆的角度范围，即 0 到 2π（或 0 到 360 度）
        //通过 i / innerSegments，我们将 i 分成 innerSegments 份，以实现将角度范围均匀地分配给内环的各个顶点
        float theta = 2.0f * M_PI_ * i / outerSegments;
        float x = outerRadius * std::cos(theta);
        float y = outerRadius * std::sin(theta);
        float z = 0.0f;

        mesh.add_vertex(MyMesh::Point(x, y, z));
    }

    // 内环的顶点
    for (int i = 0; i < innerSegments; ++i) {
        float theta = 2.0f * M_PI_ * i / innerSegments;

        for (int j = 0; j < outerSegments; ++j) {
            float phi = 2.0f * M_PI_ * j / outerSegments;

            float x = (outerRadius + innerRadius * std::cos(theta)) * std::cos(phi);
            float y = (outerRadius + innerRadius * std::cos(theta)) * std::sin(phi);
            float z = innerRadius * std::sin(theta);

            mesh.add_vertex(MyMesh::Point(x, y, z));
        }
    }

    // 创建面
    for (int i = 0; i < innerSegments; ++i) {
        for (int j = 0; j < outerSegments / 4; ++j) {//j表示象限，我只给了1/4，那就是第一象限,我觉得1/5是最合适的
            int v1 = i * outerSegments + j;
            int v2 = i * outerSegments + (j + 1) % outerSegments;
            int v3 = (i + 1) * outerSegments + j;
            int v4 = (i + 1) * outerSegments + (j + 1) % outerSegments;
            if (i == 0) {
                int v1 = (innerSegments)*outerSegments + j;
                int v2 = (innerSegments)*outerSegments + (j + 1) % outerSegments;

                int v3 = (i + 1) * outerSegments + j;
                int v4 = (i + 1) * outerSegments + (j + 1) % outerSegments;
                //std::cout << "v1:" << v1 << ",v2:" << v2 << ",v3:" << v3 << std::endl;
                mesh.add_face(mesh.vertex_handle(v1), mesh.vertex_handle(v2), mesh.vertex_handle(v3));
                mesh.add_face(mesh.vertex_handle(v2), mesh.vertex_handle(v4), mesh.vertex_handle(v3));
                continue;
            }
            mesh.add_face(mesh.vertex_handle(v1), mesh.vertex_handle(v2), mesh.vertex_handle(v3));
            //std::cout << "v1:" << v1 << ",v2:" << v2 << ",v3:" << v3 << std::endl;
            mesh.add_face(mesh.vertex_handle(v2), mesh.vertex_handle(v4), mesh.vertex_handle(v3));
        }
    }
    /*************************************************************************************************/
    // 添加圆锥 是根据上边圆柱的情况进行设计的
    float height = 1.0f;
    float radius = 0.5f;
    int slices = 30;

    //顶点
    /*
    float cone_x = 0.0 + outerRadius;
    float cone_y = 0.0 ;
    float cone_z = height ;
    */
    float cone_x = 0.0 + outerRadius;
    float cone_y = -height;
    float cone_z = 0.0;

    MyMesh::VertexHandle cone = mesh.add_vertex(MyMesh::Point(cone_x, cone_y, cone_z));
    MyMesh::VertexHandle cone_bottom = mesh.add_vertex(MyMesh::Point(cone_x, 0.0, 0.0));
    for (int i = 0; i < slices; ++i) {
        float theta1 = 2.0f * M_PI_ * i / slices;
        float theta2 = 2.0f * M_PI_ * (i + 1) / slices;

        float x1 = radius * std::cos(theta1) + outerRadius;
        float y1 = radius * std::sin(theta1);

        float x2 = radius * std::cos(theta2) + outerRadius;
        float y2 = radius * std::sin(theta2);


        /* MyMesh::VertexHandle v1 = mesh.add_vertex(MyMesh::Point(x1, y1, 0.0));
         MyMesh::VertexHandle v2 = mesh.add_vertex(MyMesh::Point(x2, y2, 0.0));*/
        MyMesh::VertexHandle v1 = mesh.add_vertex(MyMesh::Point(x1, 0.0, y1));
        MyMesh::VertexHandle v2 = mesh.add_vertex(MyMesh::Point(x2, 0.0, y2));


        // 添加侧面
        mesh.add_face(v1, v2, cone);
        //圆锥封底
        mesh.add_face(cone_bottom, v2, v1);
    }
}


/*
* 
* outerRadius: 外环的半径。
* innerRadius: 内环的半径。
* outerSegments: 外环的分段数，用于控制外环的平滑度。
* innerSegments: 内环的分段数，用于控制内环的平滑度。
*/
void create_Arrow_Curved(float outerRadius,float innerRadius,int outerSegments,int innerSegments)
{
    MyMesh mesh;
    createCompleteDonut(mesh, outerRadius, innerRadius, outerSegments, innerSegments);
    
    if (OpenMesh::IO::write_mesh(mesh, "arrow_curved.stl")) {
        std::cout << "Complete donut mesh successfully saved to arrow_curved.stl\n";
    }
    else {
        std::cerr << "Error saving mesh to arrow_curved.stl\n";
    }
}

//eg:
//int main(int argc, char* argv[])
//{
//    float outerRadius = 1.0f;
//    float innerRadius = 0.3f;
//    int outerSegments = 100;
//    int innerSegments = 50;
//    create_Arrow_Curved(outerRadius, innerRadius, outerSegments, innerSegments);
//    return 0;
//}

//int main() {
//    MyMesh mesh;
//    createCompleteDonut(mesh, 1.0f, 0.3f, 60, 30);
//
//    if (OpenMesh::IO::write_mesh(mesh, "CompleteDonut.off")) {
//        std::cout << "Complete donut mesh successfully saved to CompleteDonut.off\n";
//    }
//    else {
//        std::cerr << "Error saving mesh to CompleteDonut.off\n";
//    }
//
//    return 0;
//}