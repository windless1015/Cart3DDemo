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
    // Ĭ���ǲ�ʹ������
    m_actionUseTextureStatus = false;

    setCentralWidget(m_foxOpenGLWidget);

    // �и�
    connect(ui->actionCutting, &QAction::triggered, this, &MainWindow::slotsCuttingMesh);
    // ��ʾ
    connect(ui->actionShowTooth, &QAction::triggered, this, &MainWindow::slotsShowBeCutMesh);
    connect(ui->actionShowGingiva, &QAction::triggered, this, &MainWindow::slotsShowCutMesh);

    // ���ļ���
    connect(ui->actionOpenMeshFolder, &QAction::triggered, this, &MainWindow::slotsOpenMeshFolder);
    // ���ļ�
    connect(ui->actionOpenMeshFile, &QAction::triggered, this, &MainWindow::slotsOpenMeshFile);
    // ʹ������
    connect(ui->actionUseTexture, &QAction::triggered, this, &MainWindow::slotsUseTexture);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slotsCuttingMesh()
{
    std::cout << "�и�.........\n";
    //m_foxMeshModel->cuttingMesh();
}

void MainWindow::slotsShowCutMesh()
{
    std::cout << "��ʾ�и�����.....\n";
    //m_foxOpenGLWidget->setLoadMesh(m_foxMeshModel->getCutMesh());
    //m_foxOpenGLWidget->setVertex(m_foxMeshModel->getCutMeshVertexs());
}

void MainWindow::slotsShowBeCutMesh()
{
    std::cout << "��ʾ���и�����.......\n";
    //m_foxOpenGLWidget->setLoadMesh(m_foxMeshModel->getBeCutMesh());
    //m_foxOpenGLWidget->setVertex(m_foxMeshModel->getBeCutMehsVertexs());
}

void MainWindow::slotsOpenMeshFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("ѡ���ļ���"), QDir::homePath());

    if (!folderPath.isEmpty()) {
        // ���ļ���
        //QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
        qDebug() << "path:" << folderPath;
        m_foxOpenGLWidget->openMeshFolderPath(folderPath);
    }

}

void MainWindow::slotsOpenMeshFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("ѡ���ļ�"), "", QString::fromLocal8Bit("stl�ļ� (*.stl)"));

    if (!fileName.isEmpty()) {
        std::cout << "�򿪵��ļ�:" << fileName.toStdString()<<"\n";
        m_foxOpenGLWidget->openMeshFilePath(fileName);
    }
    else
    {
        std::cout << "δѡ���ļ�\n";
    }


}

void MainWindow::slotsUseTexture()
{
    if (!m_actionUseTextureStatus)
    {
        ui->actionUseTexture->setText(QString::fromLocal8Bit("�ر�����"));
        m_actionUseTextureStatus = true;
        m_foxOpenGLWidget->setUseTexture(m_actionUseTextureStatus);
    }
    else
    {
        ui->actionUseTexture->setText(QString::fromLocal8Bit("ʹ������"));
        m_actionUseTextureStatus = false;
        m_foxOpenGLWidget->setUseTexture(m_actionUseTextureStatus);
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{

    m_foxOpenGLWidget->keyboardPressInput(event);
}

