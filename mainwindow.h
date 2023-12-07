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
    // ��ʾ�и�ֵ�����
    void slotsShowCutMesh();
    // ��ʾ���и������
    void slotsShowBeCutMesh();

private:
   Ui::MainWindow *ui;
   FoxOpenGLWidget* m_foxOpenGLWidget;
   std::shared_ptr<FoxMeshModel> m_foxMeshModel;

};

