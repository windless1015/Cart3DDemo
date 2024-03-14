#pragma once

//define some functions to assist transform generation
//#include "Tools.h"
#include <QVector3D>
#include <QFile>
#include <QSharedPointer>


/*
 * CreateToLocalTrans
 * 创建一个从世界坐标系转换到本地坐标系的变换矩阵。
 * 输入参数:
 *   Pos: 本地坐标系原点在世界坐标系中的位置
 *   XDir: 本地坐标系X轴方向在世界坐标系中的方向
 *   YDir: 本地坐标系Y轴方向在世界坐标系中的方向
 * 返回值:
 *   一个智能指针,指向一个表示从世界坐标系到本地坐标系的变换矩阵
 */
QSharedPointer<QMatrix4x4> CreateToLocalTrans(QVector3D Pos, QVector3D XDir, QVector3D YDir);

/*
 * CreatePoseTransfrom
 * 创建一个变换矩阵,将一个坐标系的原点和轴方向转换到另一个坐标系。
 * 输入参数:
 *   fromPos: 源坐标系原点在世界坐标系中的位置
 *   fromXDir: 源坐标系X轴方向在世界坐标系中的方向
 *   fromYDir: 源坐标系Y轴方向在世界坐标系中的方向
 *   toPos: 目标坐标系原点在世界坐标系中的位置
 *   toXDir: 目标坐标系X轴方向在世界坐标系中的方向
 *   toYDir: 目标坐标系Y轴方向在世界坐标系中的方向
 * 返回值:
 *   一个智能指针,指向一个表示从源坐标系到目标坐标系的变换矩阵
 */
QSharedPointer<QMatrix4x4> CreatePoseTransfrom(QVector3D fromPos, QVector3D fromXDir, QVector3D fromYDir, QVector3D toPos, QVector3D toXDir, QVector3D toYDir);

/*
 * CreateLocalToWorldTransform
 * 创建一个从本地坐标系转换到世界坐标系的变换矩阵。
 * 输入参数:
 *   xDir: 本地坐标系X轴方向在世界坐标系中的方向
 *   yDir: 本地坐标系Y轴方向在世界坐标系中的方向
 *   zDir: 本地坐标系Z轴方向在世界坐标系中的方向
 *   origin: 本地坐标系原点在世界坐标系中的位置
 * 返回值:
 *   一个智能指针,指向一个表示从本地坐标系到世界坐标系的变换矩阵
 */
QSharedPointer<QMatrix4x4> CreateLocalToWorldTransform(double xDir[3], double yDir[3], double zDir[3], double origin[3]);

/*
 * ReadTransFromFile
 * 从文件中读取一个变换矩阵。
 * 输入参数:
 *   File: 要读取的文件
 *   DestinationXFM: 要存储读取结果的变换矩阵对象指针
 */
void ReadTransFromFile(QFile& File, QMatrix4x4* DestinationXFM);

/*
 * WriteTransToFile
 * 将一个变换矩阵写入文件。
 * 输入参数:
 *   File: 要写入的文件
 *   DestinationXFM: 要写入的变换矩阵对象指针
 */
void WriteTransToFile(QFile& File, QMatrix4x4* DestinationXFM);

/*
 * TransVectorFromTo
 * 将一个向量从一个坐标系转换到另一个坐标系。
 * 输入/输出参数:
 *   fromPos: 源坐标系原点在世界坐标系中的位置
 *   fromDir: 要转换的向量在源坐标系中的方向
 *   toPos: 目标坐标系原点在世界坐标系中的位置
 *   toDir: 转换后的向量在目标坐标系中的方向
 *   TransFromTo: 从源坐标系到目标坐标系的变换矩阵
 */
void TransVectorFromTo(QVector3D& fromPos, QVector3D& fromDir, QVector3D& toPos, QVector3D& toDir, QSharedPointer<QMatrix4x4> TransFromTo);

/*
 * CreateTransform
 * 根据两个坐标系的原点和法向量创建一个变换矩阵。
 * 输入参数:
 *   startP: 源坐标系原点在世界坐标系中的位置
 *   startNormal: 源坐标系法向量在世界坐标系中的方向
 *   endP: 目标坐标系原点在世界坐标系中的位置
 *   endNormal: 目标坐标系法向量在世界坐标系中的方向
 * 返回值:
 *   一个智能指针,指向一个表示从源坐标系到目标坐标系的变换矩阵
 */
QSharedPointer<QMatrix4x4> CreateTransform(QVector3D startP, QVector3D startNormal, QVector3D endP, QVector3D endNormal);

/*
 * CreateWorldToLocalTrans
 * 创建一个从世界坐标系转换到本地坐标系的变换矩阵。
 * 输入参数:
 *   Pos: 本地坐标系原点在世界坐标系中的位置
 *   XDir: 本地坐标系X轴方向在世界坐标系中的方向
 *   YDir: 本地坐标系Y轴方向在世界坐标系中的方向
 * 返回值:
 *   一个智能指针,指向一个表示从世界坐标系到本地坐标系的变换矩阵
 */
QSharedPointer<QMatrix4x4> CreateWorldToLocalTrans(QVector3D Pos, QVector3D XDir, QVector3D YDir);

/*
 * WriteTransformLog
 * 将一个变换矩阵写入日志文件。
 * 输入参数:
 *   name: 日志文件名称
 *   trans: 要写入的变换矩阵对象指针
 */
void WriteTransformLog(std::string name, QMatrix4x4* trans);
