#pragma once

// cart3D
#include <Util/OpenMeshUtil.h>

// Qt
#include <QVector>
#include <QVector3D>
/**
 * @brief 使用openmesh生成管道模型.
 */
class FoxPolyData;
class FoxPlane;
class FoxLine;
class FoxPipeSource 
{
public:
    FoxPipeSource();
    FoxPipeSource(const QVector< QVector3D>& pathPoints, const QVector< QVector3D>& contourPoints);
    ~FoxPipeSource() {}

    // set
    void set(const QVector< QVector3D>& pathPoints, const QVector< QVector3D>& contourPoints);
    void setPath(const QVector< QVector3D>& pathPoints);
    void setContour(const QVector< QVector3D>& contourPoints);
    void addPathPoint(const QVector3D& point);
    // get
    int getPathCount() const { return (int)m_path.size(); }
    const QVector< QVector3D>& getPathPoints() const { return m_path; }
    const QVector3D& getPathPoint(int index) const { return m_path.at(index); }
    int getContourCount() const { return (int)m_contours.size(); }
    const QVector< QVector< QVector3D> >& getContours() const { return m_contours; }
    const QVector< QVector3D>& getContour(int index) const { return m_contours.at(index); }
    const QVector< QVector< QVector3D> >& getNormals() const { return m_normals; }
    const QVector< QVector3D>& getNormal(int index) const { return m_normals.at(index); }
    // 生成openmesh网格
    Cart3D::OpenTriMesh createPipeMesh();
    std::shared_ptr<FoxPolyData> getOutputPolyData();
    // 三维线性插值函数
    QVector3D linearInterpolation3D(const QVector3D& p1, const QVector3D& p2, double t) {
        // 三维线性插值
        return p1 + (p2 - p1) * t;
    }

  
private:
	void generateContours();
	void transformFirstContour();
	QVector< QVector3D> projectContour(int fromIndex, int toIndex);
	QVector< QVector3D> computeContourNormal(int pathIndex);

	Cart3D::OpenTriMesh m_mesh;
    std::shared_ptr<FoxPolyData> m_polyData;

	QVector< QVector3D> m_path;
	QVector<QVector3D> m_contour;
	QVector< QVector<QVector3D>> m_contours;
	QVector< QVector<QVector3D>> m_normals;
};





