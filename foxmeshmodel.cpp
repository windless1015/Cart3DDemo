#include "foxmeshmodel.h"

// C++
#include <string>

//qt
#include <qdebug.h>

#include "MeshCurve/MeshSmoothCurve.h"
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

void FoxMeshModel::setMesh(std::string_view meshFilePath)
{
	IO::Options opt;
    if (IO::read_mesh(m_mesh, meshFilePath.data()), opt) {
        qDebug() << "Loaded STL file: " << meshFilePath.data();
    }
    else {
        qDebug() << "Failed to load STL file: " << meshFilePath.data();
    }
	if (!opt.check(OpenMesh::IO::Options::VertexNormal))
	{
		Logger::console_logger->info("º∆À„∑®œﬂ----");
		m_mesh.request_face_normals();
		m_mesh.update_normals();
		m_mesh.release_face_normals();
	}


}

Cart3D::OpenTriMesh FoxMeshModel::getMesh()
{
    return m_mesh;
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
		//std::string m_process_path = "E:\\learning\\Qt_learning\\Cart3D_QTDemo\\testData\\";
		//OpenMesh::IO::write_mesh(m_mesh, m_process_path + "UpperJaw_sub.stl");
		//OpenMesh::IO::write_mesh(left_mesh, m_process_path + "cut_lmesh.stl");
		//OpenMesh::IO::write_mesh(right_mesh, m_process_path + "cut_rmesh.stl");
		//clogger->info("save ok...");
	}
	clogger->info("end CurveCutMesh...");

}
