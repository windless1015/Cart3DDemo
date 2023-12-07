#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "foxopenGLwidget.h"
#include "foxmeshmodel.h"


#include <QAction>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_foxOpenGLWidget = new FoxOpenGLWidget(this);
    //foxOpenGLWidget->loadSTLFile("E:\\learning\\Qt_learning\\Cart3D_QTDemo\\testData\\lower.stl");
    //E:\\learning\\Qt_learning\\Cart3D_QTDemo\\testData\\100642730142856
    // cone.stl
    m_foxMeshModel = std::make_shared<FoxMeshModel>();
    m_foxMeshModel->setMesh("E:\\learning\\Qt_learning\\Cart3D_QTDemo\\testData\\100642730142856\\lower.stl");
    m_foxOpenGLWidget->setLoadMesh(m_foxMeshModel->getMesh());
    setCentralWidget(m_foxOpenGLWidget);

    // ÇÐ¸î
    connect(ui->actionCutting, &QAction::triggered, this, &MainWindow::slotsCuttingMesh);
    // ÏÔÊ¾
    connect(ui->actionShowL, &QAction::triggered, this, &MainWindow::slotsShowBeCutMesh);
    connect(ui->actionShowR, &QAction::triggered, this, &MainWindow::slotsShowCutMesh);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slotsCuttingMesh()
{
    std::cout << "ÇÐ¸î.........\n";
    m_foxMeshModel->cuttingMesh();
}

void MainWindow::slotsShowCutMesh()
{
    std::cout << "ÏÔÊ¾ÇÐ¸îÍø¸ñ.....\n";
    m_foxOpenGLWidget->setLoadMesh(m_foxMeshModel->getCutMesh());
}

void MainWindow::slotsShowBeCutMesh()
{
    std::cout << "ÏÔÊ¾±»ÇÐ¸îÍø¸ñ.......\n";
    m_foxOpenGLWidget->setLoadMesh(m_foxMeshModel->getBeCutMesh());
}

