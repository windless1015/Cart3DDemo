#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "view/foxopenGLwidget.h"
#include "model/foxmeshmodel.h"


#include <QAction>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDesktopServices>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_foxOpenGLWidget = new FoxOpenGLWidget(this);
    // 默认是不使用纹理
    m_actionUseTextureStatus = false;
    // 默认是不隐藏
    m_actionShowToothStatus = false;
    setCentralWidget(m_foxOpenGLWidget);


    // 切割
    connect(ui->actionCutting, &QAction::triggered, this, &MainWindow::slotsCuttingMesh);
    // 显示
    connect(ui->actionVisibleTooth, &QAction::triggered, this, &MainWindow::slotsSetVisibleTooth);
    connect(ui->actionVisibleGingiva, &QAction::triggered, this, &MainWindow::slotsSetVisibleGingiva);

    // 打开文件夹
    connect(ui->actionOpenMeshFolder, &QAction::triggered, this, &MainWindow::slotsOpenMeshFolder);
    // 打开文件
    connect(ui->actionOpenMeshFile, &QAction::triggered, this, &MainWindow::slotsOpenMeshFile);
    // 使用纹理
    connect(ui->actionUseTexture, &QAction::triggered, this, &MainWindow::slotsUseTexture);
    // 打开病例
    connect(ui->actionCaseTest1, &QAction::triggered,this,&MainWindow::slotsOpenCaseData);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slotsCuttingMesh()
{
    m_foxOpenGLWidget->cuttingMesh();
}

void MainWindow::slotsSetVisibleTooth()
{
    if (!m_actionShowToothStatus) {
        ui->actionVisibleTooth->setText(QString::fromLocal8Bit("显示牙齿"));
        m_foxOpenGLWidget->hiddenMesh();
        m_actionShowToothStatus = true;
    }
    else {
        ui->actionVisibleTooth->setText(QString::fromLocal8Bit("隐藏牙齿"));
        m_foxOpenGLWidget->showMesh();
        m_actionShowToothStatus = false;
    }
}

void MainWindow::slotsSetVisibleGingiva()
{

}

void MainWindow::slotsOpenMeshFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("选择文件夹"), QDir::homePath());

    if (!folderPath.isEmpty()) {
        // 打开文件夹
        //QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
        qDebug() << "path:" << folderPath;
        m_foxOpenGLWidget->openMeshFolderPath(folderPath);
    }

}

void MainWindow::slotsOpenMeshFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择文件"), "", QString::fromLocal8Bit("stl文件 (*.stl)"));

    if (!fileName.isEmpty()) {
        std::cout << "打开的文件:" << fileName.toStdString()<<"\n";
        m_foxOpenGLWidget->openMeshFilePath(fileName);
    }
    else
    {
        std::cout << "未选择文件\n";
    }


}

void MainWindow::slotsUseTexture()
{
    if (!m_actionUseTextureStatus)
    {
        ui->actionUseTexture->setText(QString::fromLocal8Bit("关闭纹理"));
        m_actionUseTextureStatus = true;
        m_foxOpenGLWidget->setUseTexture(m_actionUseTextureStatus);
    }
    else
    {
        ui->actionUseTexture->setText(QString::fromLocal8Bit("使用纹理"));
        m_actionUseTextureStatus = false;
        m_foxOpenGLWidget->setUseTexture(m_actionUseTextureStatus);
    }
}

void MainWindow::slotsOpenCaseData()
{
    // 打开项目内现有的数据100642730142856
    QString fileName = ".\\caseData\\100642730142856\\lower.stl";
    m_foxOpenGLWidget->openMeshFilePath(fileName);
}
