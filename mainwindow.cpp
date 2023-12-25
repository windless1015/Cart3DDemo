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

    setCentralWidget(m_foxOpenGLWidget);

    // 切割
    connect(ui->actionCutting, &QAction::triggered, this, &MainWindow::slotsCuttingMesh);
    // 显示
    connect(ui->actionShowL, &QAction::triggered, this, &MainWindow::slotsShowBeCutMesh);
    connect(ui->actionShowR, &QAction::triggered, this, &MainWindow::slotsShowCutMesh);

    // 打开文件
    connect(ui->actionOpenMeshFolder, &QAction::triggered, this, &MainWindow::slotsOpenMeshFolder);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slotsCuttingMesh()
{
    std::cout << "切割.........\n";
    //m_foxMeshModel->cuttingMesh();
}

void MainWindow::slotsShowCutMesh()
{
    std::cout << "显示切割网格.....\n";
    //m_foxOpenGLWidget->setLoadMesh(m_foxMeshModel->getCutMesh());
    //m_foxOpenGLWidget->setVertex(m_foxMeshModel->getCutMeshVertexs());
}

void MainWindow::slotsShowBeCutMesh()
{
    std::cout << "显示被切割网格.......\n";
    //m_foxOpenGLWidget->setLoadMesh(m_foxMeshModel->getBeCutMesh());
    //m_foxOpenGLWidget->setVertex(m_foxMeshModel->getBeCutMehsVertexs());
}

void MainWindow::slotsOpenMeshFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(nullptr, "选择文件夹", QDir::homePath());

    if (!folderPath.isEmpty()) {
        // 打开文件夹
        //QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
        qDebug() << "path:" << folderPath;
        m_foxOpenGLWidget->openMeshFolderPath(folderPath);
    }

}

void MainWindow::keyPressEvent(QKeyEvent* event)
{

    m_foxOpenGLWidget->keyboardPressInput(event);
}

