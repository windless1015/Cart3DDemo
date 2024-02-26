#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "view/foxopenGLwidget.h"
#include "model/foxmeshmodel.h"

#include "geometry/foxspheresource.h"

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
    initAlphaSlider();
    // Ĭ���ǲ�ʹ������
    m_actionUseTextureStatus = false;
    // Ĭ���ǲ�����
    m_actionShowToothStatus = false;
    setCentralWidget(m_foxOpenGLWidget);
    this->setWindowTitle("Cart3D_Demo");

    // �и�
    connect(ui->actionCutting, &QAction::triggered, this, &MainWindow::slotsCuttingMesh);
    // ��ʾ
    connect(ui->actionVisibleTooth, &QAction::triggered, this, &MainWindow::slotsSetVisibleTooth);
    connect(ui->actionVisibleGingiva, &QAction::triggered, this, &MainWindow::slotsSetVisibleGingiva);

    // ���ļ���
    connect(ui->actionOpenMeshFolder, &QAction::triggered, this, &MainWindow::slotsOpenMeshFolder);
    // ���ļ�
    connect(ui->actionOpenMeshFile, &QAction::triggered, this, &MainWindow::slotsOpenMeshFile);
    // ʹ������
    connect(ui->actionUseTexture, &QAction::triggered, this, &MainWindow::slotsUseTexture);
    // �򿪲���
    connect(ui->actionCaseTest1, &QAction::triggered,this,&MainWindow::slotsOpenCaseData);
    // ��ʾС��ͱ߽���
    connect(ui->actionShowSphere, &QAction::triggered, this, &MainWindow::slotsShowSphere);
    // ����
    connect(ui->actionTest, &QAction::triggered, this, &MainWindow::slotsTest);
    // ����͸����
    connect(m_setAlphaSlider, &QSlider::sliderMoved, this, &MainWindow::slotsSetAlpha);
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
        ui->actionVisibleTooth->setText(QString::fromLocal8Bit("��ʾ����"));
        m_foxOpenGLWidget->hiddenMesh();
        m_actionShowToothStatus = true;
    }
    else {
        ui->actionVisibleTooth->setText(QString::fromLocal8Bit("��������"));
        m_foxOpenGLWidget->showMesh();
        m_actionShowToothStatus = false;
    }
}

void MainWindow::slotsSetVisibleGingiva()
{

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

void MainWindow::slotsOpenCaseData()
{
    // ����Ŀ�����е�����100642730142856
    QString fileName_lower = ".\\caseData\\100642730142856\\lower.stl";
    QString fileName_upper = ".\\caseData\\100642730142856\\upper.stl";
    //m_foxOpenGLWidget->openMeshFilePath(fileName);
    m_foxOpenGLWidget->openMeshFilePath(fileName_upper, fileName_lower);
    m_setAlphaSlider->setValue(100);
    QString text = "value: 100";
    m_sliderValue->setText(text);
}

void MainWindow::slotsShowSphere()
{

    m_foxOpenGLWidget->showSphereAndLine();

}


void MainWindow::slotsTest()
{
}

void MainWindow::slotsSetAlpha(int value)
{
    float alpha = (float)(value)/100;
    QString text = "value: " + QString::number(alpha, 'f', 2);
    m_sliderValue->setText(text);
    m_foxOpenGLWidget->setActorAlpha(alpha);
}

void MainWindow::initAlphaSlider()
{
    m_sliderValue = new QLabel(this);
    m_sliderValue->setText("value: 0");
    m_sliderValue->setGeometry(width() - 300, 35, 100, 15);


    m_setAlphaSlider = new QSlider(Qt::Horizontal,this);
    // �������ֵ ��Сֵ ����
    int max = 100;
    int min = 0;
    int step = 10;
    m_setAlphaSlider->setMaximum(max);
    m_setAlphaSlider->setMinimum(min);
    m_setAlphaSlider->setSingleStep(step);

    // ����λ�� �߿�
    m_setAlphaSlider->setGeometry(width() - 170, 35, 150, 15);

    // ������ʾ���ϲ�
    m_setAlphaSlider->raise();

}
