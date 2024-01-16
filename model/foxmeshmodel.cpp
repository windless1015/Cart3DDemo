#include "foxmeshmodel.h"
#include "foxmesh.h"

// C++
#include <string>
#include <cmath>

//qt
#include <qdebug.h>
#include <qmath.h>
#include <QDir>
#include <QFileInfoList>

//Cart3d
#include <Profile/ShowData.h>
#include <Profile/DebugUtil.hpp>
#include <Sys/CPUTimer.h>
#include <MeshCurve/MeshCurveUtil.h>
#include <MeshCurve/MeshCircleCurve.h>
#include <MeshCSG/CountourCutMesh.h>
#include <Sys/Logger.h>
#include "MeshCurve/MeshSmoothCurve.h"

#include "../geometry/foxspheresource.h"

using namespace OpenMesh;
using namespace Cart3D;
FoxMeshModel::FoxMeshModel()
{
	m_isVisible = true;
}

FoxMeshModel::~FoxMeshModel()
{
	m_foxMeshs.clear();

}

void FoxMeshModel::setMeshFileName(const std::string& meshFileName)
{
	Cart3D::OpenTriMesh mesh = fileNameToMeshData(meshFileName);
	m_openTriMeshs.push_back(mesh);
}

void FoxMeshModel::setMeshFileFolder(const std::string& meshFolderPath)
{
	// 获取路径文件夹下的所有文件
	QString path = QString::fromStdString(meshFolderPath);
	QDir directory(path); // 替换为你的文件夹路径
	if (!directory.exists()) {
		qDebug() << QString::fromLocal8Bit("文件夹不存在");
		return;
	}
	directory.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	QStringList fileList = directory.entryList();
	// 遍历文件列表
	foreach(QString file, fileList) {
		// 做一个文件名拼接
		QString name = path + "\\" + file;
		std::string fileName = name.toStdString();
		// 将文件名转化为网格
		Cart3D::OpenTriMesh mesh = fileNameToMeshData(fileName);
		m_openTriMeshs.push_back(mesh);
	}

}

void FoxMeshModel::cuttingMesh()
{
	if (m_foxMeshs.empty())return;


	std::vector<cvector3d> cpts1;
	cpts1.push_back(cvector3d(-27.336922, -0.094851606, -22.03377));
	cpts1.push_back(cvector3d(-30.468161, -0.1347039, -20.110193));
	cpts1.push_back(cvector3d(-31.713745, -0.70289636, -17.194614));
	cpts1.push_back(cvector3d(-30.220974, -2.65732, -12.747708));
	cpts1.push_back(cvector3d(-26.199223, -2.8259952, -10.861499));
	cpts1.push_back(cvector3d(-22.798359, -0.83309388, -11.493107));
	cpts1.push_back(cvector3d(-20.818401, -2.0832605, -12.664121));
	cpts1.push_back(cvector3d(-20.490623, -4.0871673, -14.601606));
	cpts1.push_back(cvector3d(-20.636423, -4.1962366, -17.01095));
	cpts1.push_back(cvector3d(-21.415751, -3.6642685, -19.164167));
	cpts1.push_back(cvector3d(-23.169182, -1.9599953, -22.090446));


	std::vector<cvector3d> cpts2;
	cpts2.push_back(cvector3d(-25.249117, -2.7665837, -10.352395));
	cpts2.push_back(cvector3d(-27.17135, -3.3046055, -7.9505005));
	cpts2.push_back(cvector3d(-27.498882, -3.8595197, -4.2039275));
	cpts2.push_back(cvector3d(-26.164043, -3.9276946, -1.4192207));
	cpts2.push_back(cvector3d(-23.273211, -3.8811977, -0.43297127));
	cpts2.push_back(cvector3d(-21.230633, -1.6540283, -0.080196396));
	cpts2.push_back(cvector3d(-18.747107, -3.1219077, -0.14808056));
	cpts2.push_back(cvector3d(-16.684618, -4.3536663, -1.6568578));
	cpts2.push_back(cvector3d(-16.377636, -5.8492041, -3.521482));
	cpts2.push_back(cvector3d(-16.375031, -6.1243963, -6.8010211));
	cpts2.push_back(cvector3d(-17.218655, -5.8561997, -9.3660688));
	cpts2.push_back(cvector3d(-18.543461, -5.3723674, -11.147301));
	cpts2.push_back(cvector3d(-20.285984, -3.7182093, -12.315895));
	cpts2.push_back(cvector3d(-21.740427, -1.1696204, -11.788308));
	cpts2.push_back(cvector3d(-23.639366, -1.0700533, -10.939718));


	std::vector<cvector3d> cpts3;
	cpts3.push_back(cvector3d(-18.188932, -4.670465, 6.819068));
	cpts3.push_back(cvector3d(-18.352131, -5.234169, 7.7786584));
	cpts3.push_back(cvector3d(-18.401228, -6.2807603, 9.2176256));
	cpts3.push_back(cvector3d(-17.191866, -6.9454336, 11.233178));
	cpts3.push_back(cvector3d(-15.536585, -6.8393421, 12.017458));
	cpts3.push_back(cvector3d(-13.724133, -5.6426048, 11.86401));
	cpts3.push_back(cvector3d(-12.81056, -3.1682601, 11.402329));
	cpts3.push_back(cvector3d(-17.553946, -1.8035383, 5.8140383));
	cpts3.push_back(cvector3d(-16.614225, -3.3019154, 4.3982143));
	cpts3.push_back(cvector3d(-13.980912, -4.8374209, 4.1584334));
	cpts3.push_back(cvector3d(-12.278102, -5.4306545, 5.4551344));
	cpts3.push_back(cvector3d(-11.242167, -2.6582088, 7.8502407));
	cpts3.push_back(cvector3d(-11.313639, -4.3668957, 9.8065615));



	std::vector<cvector3d> cpts4;
	cpts4.push_back(cvector3d(-18.346313, -5.1688919, 7.2751451));
	cpts4.push_back(cvector3d(-18.355743, -6.3607259, 9.2498293));
	cpts4.push_back(cvector3d(-17.498899, -6.9941173, 10.854916));
	cpts4.push_back(cvector3d(-16.149115, -6.9906273, 11.835179));
	cpts4.push_back(cvector3d(-14.379904, -5.8321185, 12.052912));
	cpts4.push_back(cvector3d(-13.495021, -3.408103, 11.829242));
	cpts4.push_back(cvector3d(-12.23451, -3.3203826, 11.22502));
	cpts4.push_back(cvector3d(-11.345831, -3.8939056, 9.7906475));
	cpts4.push_back(cvector3d(-11.478232, -4.9086628, 7.7308111));
	cpts4.push_back(cvector3d(-12.363373, -5.1968422, 5.5811386));
	cpts4.push_back(cvector3d(-14.260139, -4.4978328, 4.1958003));
	cpts4.push_back(cvector3d(-15.771108, -3.9715636, 4.1227751));
	cpts4.push_back(cvector3d(-17.056591, -2.1704991, 5.0993047));
	cpts4.push_back(cvector3d(-17.79089, -1.9868259, 6.0915146));

	std::vector<cvector3d> cpts5;
	cpts5.push_back(cvector3d(-12.582358, -3.3381648, 11.666134));
	cpts5.push_back(cvector3d(-14.014206, -3.9816849, 12.051055));
	cpts5.push_back(cvector3d(-14.342184, -6.1697721, 12.632034));
	cpts5.push_back(cvector3d(-13.937489, -6.9620891, 14.315025));
	cpts5.push_back(cvector3d(-12.209371, -8.2242002, 16.995024));
	cpts5.push_back(cvector3d(-10.626097, -6.1651444, 17.948997));
	cpts5.push_back(cvector3d(-10.037868, -2.0048537, 17.912561));
	cpts5.push_back(cvector3d(-9.7416029, 1.1721859, 17.300463));
	cpts5.push_back(cvector3d(-9.1903801, 1.5873709, 15.495032));
	cpts5.push_back(cvector3d(-8.1640978, -3.8854644, 11.812297));
	cpts5.push_back(cvector3d(-9.1552896, -4.444663, 10.338494));
	cpts5.push_back(cvector3d(-11.487741, -3.7694452, 10.389576));


	std::vector<cvector3d> cpts6;
	cpts6.push_back(cvector3d(-7.7834578, -2.1530802, 14.905981));
	cpts6.push_back(cvector3d(-6.4329276, -3.4280555, 13.254794));
	cpts6.push_back(cvector3d(-4.4188437, -3.0670321, 14.067993));
	cpts6.push_back(cvector3d(-3.5867741, -2.4345582, 15.92662));
	cpts6.push_back(cvector3d(-4.3291655, 3.1751292, 18.960402));
	cpts6.push_back(cvector3d(-4.4297905, 1.5346444, 19.853706));
	cpts6.push_back(cvector3d(-5.1946325, -0.7056942, 20.149172));
	cpts6.push_back(cvector3d(-6.164001, -4.9282913, 19.662718));
	cpts6.push_back(cvector3d(-7.8389034, -4.722239, 18.887743));
	cpts6.push_back(cvector3d(-9.4212675, 0.23577502, 18.476448));
	cpts6.push_back(cvector3d(-9.5720129, 1.0746634, 17.22027));
	cpts6.push_back(cvector3d(-9.2036209, 1.1424763, 16.390572));


	std::vector<cvector3d> cpts7;
	cpts7.push_back(cvector3d(-4.071269, 0.52582711, 20.148998));
	cpts7.push_back(cvector3d(-3.293999, -2.4874954, 19.955072));
	cpts7.push_back(cvector3d(-2.0876503, -4.8062391, 19.951633));
	cpts7.push_back(cvector3d(-0.9180299, -4.9743333, 19.868124));
	cpts7.push_back(cvector3d(0.30988309, -3.4904525, 19.465286));
	cpts7.push_back(cvector3d(0.58994675, 2.2712257, 20.972685));
	cpts7.push_back(cvector3d(1.0164257, 3.0099375, 20.229227));
	cpts7.push_back(cvector3d(0.1049464, 0.46285087, 17.829811));
	cpts7.push_back(cvector3d(-0.33261192, -2.4247642, 15.035309));
	cpts7.push_back(cvector3d(-1.687821, -2.9007063, 14.370368));
	cpts7.push_back(cvector3d(-2.6202617, -2.1959834, 15.523156));
	cpts7.push_back(cvector3d(-4.1052241, 2.7468433, 19.384087));



	std::vector<cvector3d> cpts8;
	cpts8.push_back(cvector3d(0.96419114, 1.3393992, 20.448202));
	cpts8.push_back(cvector3d(1.5140786, 0.13337915, 20.982374));
	cpts8.push_back(cvector3d(2.2865262, -1.2807592, 20.892565));
	cpts8.push_back(cvector3d(3.010586, -5.5514808, 19.826267));
	cpts8.push_back(cvector3d(3.8876605, -5.3130431, 19.635231));
	cpts8.push_back(cvector3d(5.5072751, -0.36010981, 20.418947));
	cpts8.push_back(cvector3d(6.129776, 1.8475174, 20.081406));
	cpts8.push_back(cvector3d(5.9246683, 2.4718077, 19.295351));
	cpts8.push_back(cvector3d(4.4070225, -2.3392322, 16.459486));
	cpts8.push_back(cvector3d(3.7504518, -2.6905875, 15.380563));
	cpts8.push_back(cvector3d(2.3457928, -3.0575099, 14.269008));
	cpts8.push_back(cvector3d(1.5387377, -2.593416, 14.942922));
	cpts8.push_back(cvector3d(1.1030707, -2.3837798, 16.092196));
	cpts8.push_back(cvector3d(1.1783354, -0.3738279, 17.901476));
	cpts8.push_back(cvector3d(1.4128793, 3.1533937, 20.301474));


	std::vector<cvector3d> cpts9;
	cpts9.push_back(cvector3d(4.8379588, -2.9391317, 15.271942));
	cpts9.push_back(cvector3d(4.9827042, -3.1689694, 14.048369));
	cpts9.push_back(cvector3d(6.3446546, -3.4616058, 12.437053));
	cpts9.push_back(cvector3d(7.9090815, -2.886848, 13.260019));
	cpts9.push_back(cvector3d(9.069416, -2.4287386, 13.982512));
	cpts9.push_back(cvector3d(11.312148, 1.5496715, 16.460527));
	cpts9.push_back(cvector3d(11.041357, -0.88332003, 17.575407));
	cpts9.push_back(cvector3d(9.6435261, -5.0851369, 17.488775));
	cpts9.push_back(cvector3d(8.2688951, -5.0472035, 18.695574));
	cpts9.push_back(cvector3d(7.7670703, -2.7220356, 19.461065));
	cpts9.push_back(cvector3d(7.4782777, 0.75474524, 20.258102));
	cpts9.push_back(cvector3d(6.909801, 2.1337948, 19.757715));
	cpts9.push_back(cvector3d(5.6863708, 0.043778665, 17.718449));


	std::vector<cvector3d> cpts10;
	cpts10.push_back(cvector3d(11.247547, 0.1916654, 16.035696));
	cpts10.push_back(cvector3d(10.206238, -4.1872802, 16.283833));
	cpts10.push_back(cvector3d(10.896533, -5.6066136, 16.446676));
	cpts10.push_back(cvector3d(12.369139, -7.5373483, 16.005259));
	cpts10.push_back(cvector3d(13.724011, -7.7822781, 14.514786));
	cpts10.push_back(cvector3d(14.22681, -7.6155949, 13.156489));
	cpts10.push_back(cvector3d(14.482489, -6.4907031, 11.810171));
	cpts10.push_back(cvector3d(14.486203, -5.5617242, 10.091234));
	cpts10.push_back(cvector3d(13.586987, -5.0956874, 8.9101734));
	cpts10.push_back(cvector3d(11.615466, -4.4197083, 8.3943214));
	cpts10.push_back(cvector3d(8.9448614, -4.2788277, 8.9758406));
	cpts10.push_back(cvector3d(8.2160168, -3.719368, 10.766322));
	cpts10.push_back(cvector3d(8.2029619, -3.0353529, 12.248686));
	cpts10.push_back(cvector3d(11.155627, 2.3003578, 14.345672));
	cpts10.push_back(cvector3d(11.387909, 1.3670833, 15.644484));

	std::vector<cvector3d> cpts11;
	cpts11.push_back(cvector3d(12.777137, -2.8475018, 6.8231363));
	cpts11.push_back(cvector3d(13.001207, -4.6369767, 7.8478403));
	cpts11.push_back(cvector3d(14.11776, -4.9072151, 8.5552139));
	cpts11.push_back(cvector3d(15.790359, -6.0507317, 9.115921));
	cpts11.push_back(cvector3d(16.562334, -7.6039858, 8.917408));
	cpts11.push_back(cvector3d(19.019053, -5.2085748, 8.4003782));
	cpts11.push_back(cvector3d(19.082623, -7.2148118, 6.5247531));
	cpts11.push_back(cvector3d(19.667524, -4.8991108, 5.143271));
	cpts11.push_back(cvector3d(18.974867, -4.8967066, 2.5008621));
	cpts11.push_back(cvector3d(17.585649, -3.8684525, 1.597535));
	cpts11.push_back(cvector3d(15.853637, -2.8488293, 1.5590898));
	cpts11.push_back(cvector3d(14.590376, -2.089046, 2.044188));
	cpts11.push_back(cvector3d(12.527287, -3.9754755, 2.9105079));
	cpts11.push_back(cvector3d(11.775646, -3.6760767, 4.8131895));

	std::vector<cvector3d> cpts12;
	cpts12.push_back(cvector3d(11.839733, -2.9831023, 1.9266813));
	cpts12.push_back(cvector3d(13.647088, -1.7174091, 2.0461712));
	cpts12.push_back(cvector3d(16.278019, -2.6051631, 1.171901));
	cpts12.push_back(cvector3d(18.088385, -3.0559075, -0.29641956));
	cpts12.push_back(cvector3d(17.900049, -0.73675489, -1.7471105));
	cpts12.push_back(cvector3d(17.160749, -1.915924, -3.6760347));
	cpts12.push_back(cvector3d(14.390267, -0.82501984, -5.2141581));
	cpts12.push_back(cvector3d(12.131792, -1.7109632, -5.4440398));
	cpts12.push_back(cvector3d(11.879443, -4.009007, -5.7910743));
	cpts12.push_back(cvector3d(10.308355, -5.6151848, -3.9092295));
	cpts12.push_back(cvector3d(9.5760298, -5.322587, -1.9648372));
	cpts12.push_back(cvector3d(10.204887, -4.6895261, 0.74256426));

	std::vector<cvector3d> cpts13;
	cpts13.push_back(cvector3d(15.870631, -1.2171853, -4.6270294));
	cpts13.push_back(cvector3d(17.955923, -1.729513, -4.5796328));
	cpts13.push_back(cvector3d(19.03544, -1.1664386, -5.240777));
	cpts13.push_back(cvector3d(20.32023, -1.5739945, -6.5284367));
	cpts13.push_back(cvector3d(21.05479, -1.623525, -8.1560879));
	cpts13.push_back(cvector3d(21.791681, -1.9451352, -9.6225662));
	cpts13.push_back(cvector3d(21.973808, -2.0137627, -11.123976));
	cpts13.push_back(cvector3d(21.87726, -2.4317932, -12.42795));
	cpts13.push_back(cvector3d(19.941048, -1.9218801, -13.512549));
	cpts13.push_back(cvector3d(18.629719, -1.9006255, -14.248943));
	cpts13.push_back(cvector3d(16.79385, -2.2356694, -14.891855));
	cpts13.push_back(cvector3d(15.06279, -2.9714255, -14.599661));
	cpts13.push_back(cvector3d(13.862517, -4.4525418, -13.672205));
	cpts13.push_back(cvector3d(12.645838, -5.2416382, -12.142212));
	cpts13.push_back(cvector3d(12.074322, -6.0036707, -10.41911));
	cpts13.push_back(cvector3d(11.294023, -6.0649462, -8.448658));
	cpts13.push_back(cvector3d(11.521647, -4.8135476, -6.7312393));
	cpts13.push_back(cvector3d(13.016018, -0.95764065, -5.2894988));
	cpts13.push_back(cvector3d(14.59846, -0.66622066, -4.9706116));

	std::vector<cvector3d> cpts14;
	cpts14.push_back(cvector3d(15.896909, -4.2679381, -16.875547));
	cpts14.push_back(cvector3d(16.683147, -3.834502, -15.634482));
	cpts14.push_back(cvector3d(17.982008, -1.9987004, -14.88921));
	cpts14.push_back(cvector3d(20.292591, -1.5469366, -13.964835));
	cpts14.push_back(cvector3d(22.65583, -2.0313995, -13.779329));
	cpts14.push_back(cvector3d(24.632381, -1.8323059, -14.849691));
	cpts14.push_back(cvector3d(26.008675, -1.7913207, -16.431713));
	cpts14.push_back(cvector3d(26.683199, -1.172011, -19.09758));
	cpts14.push_back(cvector3d(26.182919, -0.16124144, -21.225208));
	cpts14.push_back(cvector3d(24.356983, 0.15415268, -22.31641));
	cpts14.push_back(cvector3d(21.936338, -1.0188662, -23.127558));
	cpts14.push_back(cvector3d(21.072323, -2.3362017, -24.408916));
	cpts14.push_back(cvector3d(20.849037, -4.4965792, -25.09868));
	cpts14.push_back(cvector3d(19.395172, -4.2501612, -24.327147));
	cpts14.push_back(cvector3d(18.345518, -4.2088146, -22.782297));
	cpts14.push_back(cvector3d(17.377153, -5.4181013, -21.519199));
	cpts14.push_back(cvector3d(16.427122, -6.4739175, -19.971867));
	cpts14.push_back(cvector3d(15.802121, -5.9943495, -18.074095));


	std::vector<std::vector<cvector3d>> cptslist;
	cptslist.push_back(cpts1);
	cptslist.push_back(cpts2);
	cptslist.push_back(cpts3);
	cptslist.push_back(cpts4);
	cptslist.push_back(cpts5);
	cptslist.push_back(cpts6);
	cptslist.push_back(cpts7);
	cptslist.push_back(cpts8);
	cptslist.push_back(cpts9);
	cptslist.push_back(cpts10);
	cptslist.push_back(cpts11);
	cptslist.push_back(cpts12);
	cptslist.push_back(cpts13);
	cptslist.push_back(cpts14);


	m_mesh = m_openTriMeshs[0];
	std::shared_ptr<fcpw::Scene<3>> tree;
	m_openTriMeshs.clear();
	// 用于构建几何查询场景
	bool res = MeshCurveUtil::create_scene3d(m_mesh, tree);
	if (res) {
		clogger->info("create_scene3D is ok");
	}
	// 遍历边界线进行分割
	//int i = 0;
	for (std::vector<cvector3d> cpts : cptslist) {
		Cart3D::OpenTriMesh left_mesh, right_mesh;
		if (CountourCutMesh::countour_cut_mesh(m_mesh,tree, cpts, left_mesh, right_mesh, true))
		{
			//std::string name = "right_mesh" + std::to_string(i) + ".stl";
			//IO::write_mesh(left_mesh, "E:\\3D\\TestData\\testData\\100642730142856\\test\\left_mesh.stl");
			//IO::write_mesh(right_mesh, "E:\\3D\\TestData\\testData\\100642730142856\\test\\"+name);
			m_openTriMeshs.push_back(right_mesh);
		}
		//++i;
	}
	clogger->info("end CurveCutMesh...");
	m_foxMeshs.clear();
}

void FoxMeshModel::showSphere(QOpenGLShaderProgram* shader)
{
	// 创建小球
	Cart3D::OpenTriMesh mesh;
	FoxSphereSource sphere;
	sphere.setRadius(1.5f);
	sphere.setCenter(-27.336922, -0.094851606, -22.03377);
	// 获取小球数据
	sphere.getSphereMesh(mesh);
	mesh.request_vertex_normals();
	setMeshNormals(mesh);
	std::vector<float> vertex = meshDataToVertexData(mesh);
	// 传入mesh
	sptr_FoxMesh foxMesh = std::make_shared<FoxMesh>(vertex, shader);

	//-30.468161, -0.1347039, -20.110193
		// 创建小球
	Cart3D::OpenTriMesh mesh2;
	FoxSphereSource sphere2;
	sphere2.setRadius(1.5f);
	sphere2.setCenter(-30.468161, -0.1347039, -20.110193);
	// 获取小球数据
	sphere2.getSphereMesh(mesh2);
	mesh2.request_vertex_normals();
	setMeshNormals(mesh2);
	std::vector<float> vertex2 = meshDataToVertexData(mesh2);
	// 传入mesh
	sptr_FoxMesh foxMesh2 = std::make_shared<FoxMesh>(vertex2, shader);

	m_foxMeshs.push_back(foxMesh);

}


void FoxMeshModel::loadMesh(QOpenGLShaderProgram* shader)
{
	if (!m_isVisible) return;
	// 绘制网格
	for (auto i : m_foxMeshs) {
		i->darw(shader);
	}
}

void FoxMeshModel::addMesh(QOpenGLShaderProgram* shader)
{
	//m_shaderProgram = shader;
	// 将网格转换为顶点数据添加至Foxmesh类中
	for (auto& mesh : m_openTriMeshs)
	{
		mesh.request_vertex_normals();
		setMeshNormals(mesh);
		std::vector<float> vertex = meshDataToVertexData(mesh);
		sptr_FoxMesh foxmesh = std::make_shared<FoxMesh>(vertex, shader);
		m_foxMeshs.push_back(foxmesh);
	}
}


void FoxMeshModel::setVisible(bool isVisible)
{
	m_isVisible = isVisible;
}



std::vector<float> FoxMeshModel::meshDataToVertexData(Cart3D::OpenTriMesh& mesh)
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
			float u = (qAtan2(normal[1], normal[0]) / (2 * M_PI));
			float v = (qAsin(normal[2]) / M_PI);
			if (u < 0.0) u *= -1.0;
			if (v < 0.0) v *= -1.0;
			vertex.push_back(u);
			vertex.push_back(v);
		}
	}
	return vertex;
}

Cart3D::OpenTriMesh FoxMeshModel::fileNameToMeshData(const std::string& fileName)
{
	Cart3D::OpenTriMesh mesh;
	mesh.request_vertex_normals();
	if (IO::read_mesh(mesh, fileName.data())) {
		qDebug() << "Loaded STL file: " << fileName.data();
		setMeshNormals(mesh);
	}
	else {
		qDebug() << "Failed to load STL file: " << fileName.data();
	}
	return mesh;
}

void FoxMeshModel::setMeshNormals(Cart3D::OpenTriMesh& mesh)
{

	if (!mesh.has_vertex_normals())
	{
		Cart3D::Logger::console_logger->error("法线异常!!!!!");
		return;
	}
	// 计算法线
	mesh.request_face_normals();
	mesh.update_normals();
	mesh.release_face_normals();

}


