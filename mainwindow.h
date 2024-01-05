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

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
   Ui::MainWindow *ui;
   FoxOpenGLWidget* m_foxOpenGLWidget;
   // 纹理开个状态  true:开   false:关
   bool m_actionUseTextureStatus;
   bool m_actionShowToothStatus;
};

