#pragma once

#include <memory>
#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include <QLayout>

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
    // �и�
    void slotsCuttingMesh();
    // ��ʾ����
    void slotsSetVisibleTooth();
    // ��ʾ����
    void slotsSetVisibleGingiva();
    // ���ļ���
    void slotsOpenMeshFolder();
    // ���ļ�
    void slotsOpenMeshFile();
    // ʹ������
    void slotsUseTexture();
    // �򿪲���
    void slotsOpenCaseData();
    // ��ʾС��
    void slotsShowSphere();
    // ���ڲ��Ե�
    void slotsTest();
    // ����͸����
    void slotsSetAlpha(int value);
    // ��ʾ����洰��
    void slotsShow2DCrossSectionWidget();

private:
    // ��ʼ������
    void initAlphaSlider();
    
private:
   Ui::MainWindow *ui;
   FoxOpenGLWidget* m_foxOpenGLWidget;
   Fox2DCrossSectionWidget* m_fox2DCrossSectionWidget;
   // ������״̬  true:��   false:��
   bool m_actionUseTextureStatus;
   bool m_actionShowToothStatus;
   QSlider* m_setAlphaSlider;
   QLabel* m_sliderValue;
};

