
#include "foxpipesource.h"

#include <QMatrix4x4>

#include <QVector2D>

#include "foxline.h"
#include "foxplane.h"
#include "../rendering/foxpolydata.h"
/**
 * @brief 管道类的部分.
 * ==============================================
 * @{
 */
FoxPipeSource::FoxPipeSource()
{
}

FoxPipeSource::FoxPipeSource(const QVector<QVector3D>& pathPoints, const QVector<QVector3D>& contourPoints)
{
	set(pathPoints, contourPoints);
}

void FoxPipeSource::set(const QVector<QVector3D>& pathPoints, const QVector<QVector3D>& contourPoints)
{
	this->m_path = pathPoints;
	this->m_contour = contourPoints;
	generateContours();
}

void FoxPipeSource::setPath(const QVector<QVector3D>& pathPoints)
{
	this->m_path = pathPoints;
	generateContours();
}

void FoxPipeSource::setContour(const QVector<QVector3D>& contourPoints)
{
	this->m_contour = contourPoints;
	generateContours();
}

void FoxPipeSource::addPathPoint(const QVector3D& point)
{
    m_path.push_back(point);

    int count = m_path.size();
    if (count == 1)
    {
        transformFirstContour();
        m_normals.push_back(computeContourNormal(0));
    }
    else if (count == 2)
    {
        m_contours.push_back(projectContour(0, 1));
        m_normals.push_back(computeContourNormal(1));
    }
    else
    {
        QVector<QVector3D> dummy;
        m_contours.push_back(dummy);
        m_normals.push_back(dummy);

        m_contours[count - 2] = projectContour(count - 3, count - 2);
        m_normals[count - 2] = computeContourNormal(count - 2);

        m_contours[count - 1] = projectContour(count - 2, count - 1);
        m_normals[count - 1] = computeContourNormal(count - 1);
    }
}

Cart3D::OpenTriMesh FoxPipeSource::createPipeMesh()
{


    int count = this->m_contours.size();
    std::vector<Cart3D::OpenTriMesh::VertexHandle> vh1;
    std::vector<Cart3D::OpenTriMesh::VertexHandle> vh2;
    std::vector<Cart3D::OpenTriMesh::VertexHandle> face_vhandles;
    
    for (int i = 0; i < count - 1; i++) {
        auto& begin = m_contours.at(i);
        auto& next = m_contours.at(i + 1);
        for (int j = 0; j < next.size(); j++) {
            vh1.push_back(m_mesh.add_vertex(Cart3D::OpenTriMesh::Point(begin[j].x(), begin[j].y(), begin[j].z())));
            vh2.push_back(m_mesh.add_vertex(Cart3D::OpenTriMesh::Point(next[j].x(), next[j].y(), next[j].z())));
        }
    }



    for (int i = 0; i < vh2.size()-1; i++) {
        face_vhandles.clear();
        face_vhandles.push_back(vh2.at(i));
        face_vhandles.push_back(vh1.at(i));
        face_vhandles.push_back(vh1.at(i + 1));
        face_vhandles.push_back(vh2.at(i + 1));
        m_mesh.add_face(face_vhandles);
    }

    return m_mesh;
}

std::shared_ptr<FoxPolyData> FoxPipeSource::getOutputPolyData()
{

    m_mesh = createPipeMesh();
    // 将网格数据添加至FoxPolyData
    m_polyData = std::make_shared<FoxPolyData>(m_mesh);
    return m_polyData;
}

void FoxPipeSource::generateContours()
{
    // reset
    m_contours.clear();
    m_normals.clear();

    // path must have at least a point
    if (m_path.size() < 1)
        return;

    // rotate and translate the contour to the first path point
    // 旋转并平移轮廓到第一个路径点 
    transformFirstContour();
    m_contours.push_back(this->m_contour);
    m_normals.push_back(computeContourNormal(0));

    // project contour to the plane at the next path point
    // 将等高线投影到下一个路径点的平面上
    int count = (int)m_path.size();
    for (int i = 1; i < count; ++i)
    {
        m_contours.push_back(projectContour(i - 1, i));
        m_normals.push_back(computeContourNormal(i));
    }

}

void FoxPipeSource::transformFirstContour()
{
    int pathCount = (int)m_path.size();
    int vertexCount = (int)m_contour.size();
    QMatrix4x4 matrix;
    if (pathCount > 0)
    {

        matrix.translate(m_path[0]);
        matrix.scale(0.6f);
        //if (pathCount > 1)
        //    matrix.rotate(67.0f, m_path[0]);
        //将矩阵与等高线相乘注意:这里是等值线顶点的变换如果路径被重置为0，必须重新提交轮廓线数据
        for (int i = 0; i < vertexCount; ++i)
        {
            m_contour[i] = matrix * m_contour[i];
        }
    }

}

QVector<QVector3D> FoxPipeSource::projectContour(int fromIndex, int toIndex)
{
    QVector3D dir1, dir2, normal;
    FoxLine line;

    dir1 = m_path[toIndex] - m_path[fromIndex];
    if (toIndex == (int)m_path.size() - 1)
        dir2 = dir1;
    else
        dir2 = m_path[toIndex + 1] - m_path[toIndex];

    normal = dir1 + dir2;               // 平面在顶点处的法向量
    FoxPlane plane(normal, m_path[toIndex]);

    // 将等高线的每个顶点投影到平面上
    QVector3D v;
    QVector<QVector3D>& fromContour = m_contours[fromIndex];
    QVector<QVector3D> toContour;

    int count = (int)fromContour.size();
    for (int i = 0; i < count; ++i)
    {
        line.set(dir1, fromContour[i]);
        toContour.push_back(plane.intersect(line));
    }
    return toContour;
}

QVector<QVector3D> FoxPipeSource::computeContourNormal(int pathIndex)
{
    QVector<QVector3D>& contour = m_contours[pathIndex];
    QVector3D center = m_path[pathIndex];

    QVector<QVector3D> contourNormal;
    QVector3D normal;
    for (int i = 0; i < (int)contour.size(); ++i)
    {
        normal = (contour[i] - center).normalized();
        contourNormal.push_back(normal);
    }

    return contourNormal;
}

/**
 * ================================================.
 * @}.
 */




