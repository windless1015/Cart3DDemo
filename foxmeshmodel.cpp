#include "foxmeshmodel.h"

// C++
#include <string>
#include <cmath>

//qt
#include <qdebug.h>

#include "MeshCurve/MeshSmoothCurve.h"

#include <qmath.h>

//Cart3d
#include <Profile/ShowData.h>
#include <Profile/DebugUtil.hpp>
#include <Sys/CPUTimer.h>
#include <MeshCurve/MeshCurveUtil.h>
#include <MeshCurve/MeshCircleCurve.h>
#include <MeshCSG/CountourCutMesh.h>
#include <Sys/Logger.h>


using namespace OpenMesh;
using namespace Cart3D;
FoxMeshModel::FoxMeshModel()
{
}

FoxMeshModel::~FoxMeshModel()
{
}

void FoxMeshModel::setMeshFilePath(const std::string& meshFilePath)
{
	IO::Options opt;
	m_mesh.request_vertex_normals();
    if (IO::read_mesh(m_mesh, meshFilePath.data()), opt) {
        qDebug() << "Loaded STL file: " << meshFilePath.data();
    }
    else {
        qDebug() << "Failed to load STL file: " << meshFilePath.data();
    }
	if (!opt.check(OpenMesh::IO::Options::VertexNormal))
	{
		Logger::console_logger->info("计算法线----");
		m_mesh.request_face_normals();
		m_mesh.update_normals();
		m_mesh.release_face_normals();
	}


}

Cart3D::OpenTriMesh FoxMeshModel::getMesh()
{
    return m_mesh;
}

std::vector<float> FoxMeshModel::getMeshVertexs()
{
	std::vector<float> vertexs = meshDataToVertexData(m_mesh);
	return vertexs;
}

void FoxMeshModel::cuttingMesh()
{
    std::vector<cvector3d> cpts;
	cpts.push_back(cvector3d(-20.440506, -2.771281, -12.405457));
	cpts.push_back(cvector3d(-21.386002, -1.22525, -11.865996));
	cpts.push_back(cvector3d(-23.852659, -1.4405715, -10.69147));
	cpts.push_back(cvector3d(-27.45927, -3.5105646, -8.6007729));
	cpts.push_back(cvector3d(-27.989351, -3.8170638, -5.4327502));
	cpts.push_back(cvector3d(-18.487795, -4.7283449, -11.327295));
	cpts.push_back(cvector3d(-17.133171, -5.6555552, -9.5850964));
	cpts.push_back(cvector3d(-16.502098, -6.3037839, -7.7498207));
	cpts.push_back(cvector3d(-15.879408, -4.814425, -4.8580675));
	cpts.push_back(cvector3d(-16.654034, -5.0340104, -1.7170566));

	cpts.push_back(cvector3d(-18.594997, -3.276701, 0.053426754));
	cpts.push_back(cvector3d(-20.99946, -1.7903191, 0.29733023));
	cpts.push_back(cvector3d(-25.049479, -4.3522773, 0.41840598));

	Cart3D::OpenTriMesh left_mesh, right_mesh;

	std::shared_ptr<fcpw::Scene<3>> tree;
	bool res = MeshCurveUtil::create_scene3d(m_mesh, tree);
	if (res) {
		clogger->info("create_scene3D is ok");
	}


	if (CountourCutMesh::countour_cut_mesh(m_mesh, tree, cpts, left_mesh, right_mesh, true))
	{
		m_cutMesh = right_mesh;
		m_beCutMesh = left_mesh;
	}
	clogger->info("end CurveCutMesh...");

}

Cart3D::OpenTriMesh FoxMeshModel::getCutMesh()
{
	return m_cutMesh;
}

Cart3D::OpenTriMesh FoxMeshModel::getBeCutMesh()
{
	return m_cutMesh;
}

std::vector<float> FoxMeshModel::meshDataToVertexData(Cart3D::OpenTriMesh mesh)
{
	std::vector<float> vertex;
	// 遍历面片
	for (Cart3D::OpenTriMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it)
	{
		// 遍历面片上的顶点
		for (Cart3D::OpenTriMesh::FaceVertexIter fv_it = mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
		{
			// 获取每个面片上的点
			auto& point = mesh.point(*fv_it);
			// 获取法向量
			auto& normal = mesh.normal(*fv_it);
			vertex.push_back(point[0]);
			vertex.push_back(point[1]);
			vertex.push_back(point[2]);
			// 添加法向量
			vertex.push_back(normal[0]);
			vertex.push_back(normal[1]);
			vertex.push_back(normal[2]);
			// 添加纹理坐标
			//float u = point[0] / SCR_WIDTH;
			//float v = point[1] / SCR_HEIGHT;
			float u = 0.5+(qAtan2(point[1], point[0]) / (2 * M_PI));
			float v = 0.5 - (qAsin(point[2]) / M_PI);

			vertex.push_back(u);
			vertex.push_back(v);
		}
	}

	return vertex;
}
