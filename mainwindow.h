#pragma once

#include <memory>
#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include <QLayout>
#include "common.h"
#include <QMessageBox>
#include <string>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FoxOpenGLWidget;
class FoxMeshModel;
class Fox2DCrossSectionWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 切割
    void slotsCuttingMesh();
    // 显示牙齿
    void slotsSetVisibleTooth();
    // 显示牙龈
    void slotsSetVisibleGingiva();
    // 打开文件夹
    void slotsOpenMeshFolder();
    // 打开文件
    void slotsOpenMeshFile();
    // 使用纹理
    void slotsUseTexture();
    // 打开病例
    void slotsOpenCaseData();

    // 显示小球
    void slotsShowSphere();
    // 用于测试的
    void slotsTest();
    // 设置透明度
    void slotsSetAlpha(int value);
    // 显示横截面窗口
    void slotsShow2DCrossSectionWidget();

    //状态栏的显示
    void slots_statusbar_text_show(QString text);

    //wxn:
    //添加附件
    void slotsAddAttachment();
    //添加一些组件(仅仅用于测试)
    //按钮名:actionTestComponent
    void slotsAddTestComponent();


    // ������������
    void slotsOpenInvisalignData();

    void slotsAbout();

    //坐标系(直接读取stl模型)
    void slotsCoordinate_System();
    void slots_Change_to_Classic_mode();
    void slots_Change_to_ArcBall_mode();
    void slots_Change_to_Sphere_mode();
    void slots_Change_Add_Axis_2();
    void slots_Change_Add_Axis_3();
    void slots_Change_GridMode_EnableDeepTesting();
    void slots_Change_GridMode_ProhibitDeepTesting();
private:
    // 初始化滑块
    void initAlphaSlider();
    void updateAlphaSlider();
private:
   Ui::MainWindow *ui;
   FoxOpenGLWidget* m_foxOpenGLWidget;
   Fox2DCrossSectionWidget* m_fox2DCrossSectionWidget;
   // 纹理开个状态  true:开   false:关
   bool m_actionUseTextureStatus;
   bool m_actionShowToothStatus;
   QSlider* m_setAlphaSlider;
   QLabel* m_sliderValue;

signals:
    void opengl_Draw_coordinate_system_flag(QString text);
    void Change_GridMode(QString text);
};

