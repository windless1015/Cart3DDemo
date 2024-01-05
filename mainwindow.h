#pragma once

#include <memory>
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FoxOpenGLWidget;
class FoxMeshModel;
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

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
   Ui::MainWindow *ui;
   FoxOpenGLWidget* m_foxOpenGLWidget;
   // ������״̬  true:��   false:��
   bool m_actionUseTextureStatus;
   bool m_actionShowToothStatus;
};

