#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "view/foxopenGLwidget.h"
#include "view/fox2dcrosssectionwidget.h"

#include "model/foxmeshmodel.h"

#include "geometry/foxspheresource.h"

#include <QAction>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDesktopServices>
#include <QIcon>
#include <QSpacerItem>


#include "circle.hpp"
#include "arrow.hpp"
#include "arrow_curved.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_foxOpenGLWidget = new FoxOpenGLWidget(this);

    m_fox2DCrossSectionWidget = new Fox2DCrossSectionWidget();

    QAction* actionCrossSection = new QAction(QIcon(".\\res\\icon\\2d_cross_section24x24.png"), tr("2D Cross Section"), this);
    ui->toolBar->addAction(actionCrossSection);

    initAlphaSlider();
    // 默认是不使用纹理
    m_actionUseTextureStatus = false;
    // 默认是不隐藏
    m_actionShowToothStatus = false;
    setCentralWidget(m_foxOpenGLWidget);

    this->setWindowTitle("Cart3D_Demo");
    slots_statusbar_text_show(QString::fromLocal8Bit("当前的旋转模式:ClassMode"));

    // 切割
    connect(ui->actionCutting, &QAction::triggered, this, &MainWindow::slotsCuttingMesh);
    // 显示
    connect(ui->actionVisibleTooth, &QAction::triggered, this, &MainWindow::slotsSetVisibleTooth);
    connect(ui->actionVisibleGingiva, &QAction::triggered, this, &MainWindow::slotsSetVisibleGingiva);
    connect(actionCrossSection, &QAction::triggered, this, &MainWindow::slotsShow2DCrossSectionWidget);

    // 打开文件夹
    connect(ui->actionOpenMeshFolder, &QAction::triggered, this, &MainWindow::slotsOpenMeshFolder);
    // 打开文件
    connect(ui->actionOpenMeshFile, &QAction::triggered, this, &MainWindow::slotsOpenMeshFile);
    // 使用纹理
    connect(ui->actionUseTexture, &QAction::triggered, this, &MainWindow::slotsUseTexture);
    // 打开1428...病例
    connect(ui->actionCaseTest1, &QAction::triggered, this, &MainWindow::slotsOpenCaseData);
    // 显示小球和边界线
    connect(ui->actionShowSphere, &QAction::triggered, this, &MainWindow::slotsShowSphere);
    // 测试
    connect(ui->actionTest, &QAction::triggered, this, &MainWindow::slotsTest);
    // 设置透明度
    connect(m_setAlphaSlider, &QSlider::sliderMoved, this, &MainWindow::slotsSetAlpha);


    //wxn:
     //添加附件
    connect(ui->actionAddAttachment, &QAction::triggered, this, &MainWindow::slotsAddAttachment);
    connect(ui->actionTestComponent, &QAction::triggered, this, &MainWindow::slotsAddTestComponent);
    

    //隐适美的那个病例
    connect(ui->actionOpenTestData_2, &QAction::triggered, this, &MainWindow::slotsOpenInvisalignData);

    //软件说明
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::slotsAbout);

    /**
     * @brief 添加坐标系
     * @doubt 为何先加载病例再加载坐标系,坐标系不会消失,
     * 但是,先加载坐标系再加载病例,坐标系便会消失?
     */
    connect(ui->action_Coordinate_System, &QAction::triggered, this, &MainWindow::slotsCoordinate_System);


    connect(ui->ClassicModeAction, &QAction::triggered, this, &MainWindow::slots_Change_to_Classic_mode);
    connect(ui->ArcBallAction, &QAction::triggered, this, &MainWindow::slots_Change_to_ArcBall_mode);
    connect(ui->actionsphere, &QAction::triggered, this, &MainWindow::slots_Change_to_Sphere_mode);
       
    // 坐标轴
    //action_CS_2
    connect(ui->action_CS_2, &QAction::triggered, this, &MainWindow::slots_Change_Add_Axis_2);
    connect(ui->action_CS_3, &QAction::triggered, this, &MainWindow::slots_Change_Add_Axis_3);
    //connect(m_foxOpenGLWidget, &FoxOpenGLWidget::, this, &MainWindow::);
    //自定义信号与槽
    connect(this, &MainWindow::opengl_Draw_coordinate_system_flag,m_foxOpenGLWidget, &FoxOpenGLWidget::RePaintGL_coordinate_system);

    //网格绘制
    //ProhibitDeepTestingAction
    //EnableDeepTestingAction
    connect(ui->EnableDeepTestingAction, &QAction::triggered, this, &MainWindow::slots_Change_GridMode_EnableDeepTesting);
    connect(ui->ProhibitDeepTestingAction, &QAction::triggered, this, &MainWindow::slots_Change_GridMode_ProhibitDeepTesting);
    connect(this, &MainWindow::Change_GridMode, m_foxOpenGLWidget, &FoxOpenGLWidget::RePaintGL_Grid);

    //QOpenGLWidget与Mainwindow状态栏的绑定
    connect(m_foxOpenGLWidget, &FoxOpenGLWidget::statusbar_text, this, &MainWindow::slots_statusbar_text_show);
    
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_fox2DCrossSectionWidget;
}


void MainWindow::slotsCuttingMesh()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("调用切割算法"));
    m_foxOpenGLWidget->cuttingMesh();
}

void MainWindow::slotsSetVisibleTooth()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("设置牙齿的可见性"));
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
    slots_statusbar_text_show(QString::fromLocal8Bit("设置牙龈的可见性"));
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
        std::cout << "打开的文件:" << fileName.toStdString() << "\n";
        m_foxOpenGLWidget->openMeshFilePath(fileName);
    }
    else
    {
        std::cout << "未选择文件\n";
    }


}

void MainWindow::slotsUseTexture()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("暂时只针对映射美模型进行纹理贴图..."));
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
    isLoading = true;

    // 打开项目内现有的数据100642730142856
    QString fileName_lower = ".\\caseData\\100642730142856\\lower.stl";
    QString fileName_upper = ".\\caseData\\100642730142856\\upper.stl";
    //m_foxOpenGLWidget->openMeshFilePath(fileName);
    m_foxOpenGLWidget->openMeshFilePath(fileName_upper, fileName_lower);
    updateAlphaSlider();
}


/*
    (8.6045361, -1.9544933, 19.358801)
(13.16833, -3.2849004, 16.512573)
(3.312443, -1.3500501, 20.896019)
(-1.4881694, -1.3923264, 20.80794)
(-5.610785, -1.7306153, 20.031492)
(-11.10446, -2.4184246, 18.264595)
(-22.126347, -2.9033034, 7.3613696)
(-24.320957, -0.48074791, -1.9065716)
(-28.78474, 0.87899041, -12.942302)
(17.909452, -4.9347744, 8.9049664)
(16.049683, -0.60370404, 0.48569041)
(19.560465, -0.39529461, -7.0728149)
(24.270132, -1.4246315, -15.168131)
    */
void MainWindow::slotsAddAttachment()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("添加附件"));
    if (isLoading == false) {
        QMessageBox::information(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请先加载病人牙齿"));
    }
    else {
        QMessageBox::information(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("正在添加附件,请稍后..."));
        QVector3D qv3d[13] = { 
            QVector3D(8.6045361, -1.9544933, 19.358801),
            QVector3D(13.16833, -3.2849004, 16.512573),
            QVector3D(3.312443, -1.3500501, 20.896019),
            QVector3D(-1.4881694, -1.3923264, 20.80794),
            QVector3D(-5.610785, -1.7306153, 20.031492),
            QVector3D(-11.10446, -2.4184246, 18.264595),
            QVector3D(-22.126347, -2.9033034, 7.3613696),
            QVector3D(-24.320957, -0.48074791, -1.9065716),
            QVector3D(-28.78474, 0.87899041, -12.942302),
            QVector3D(17.909452, -4.9347744, 8.9049664),
            QVector3D(16.049683, -0.60370404, 0.48569041),
            QVector3D(19.560465, -0.39529461, -7.0728149),
            QVector3D(24.270132, -1.4246315, -15.168131) };
;        //加载附件,然后把附件贴上去
        //../a1.stl
        QString fileName_Attachment = "../a1.stl";
        //qDebug() << "Test:============================>" << sizeof(qv3d) / sizeof(QVector3D);
        for(int i = 0 ; i< sizeof(qv3d)/ sizeof(QVector3D);i++){
            m_foxOpenGLWidget->openAttachmentFilePath(fileName_Attachment, qv3d[i]);
        }
    }
}

void MainWindow::slotsAddTestComponent()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("在可执行文件目录下生成圆盘,直箭头和弯曲的箭头,但是还没有在widget上显示"));
    QMessageBox::information(nullptr, QString::fromLocal8Bit("Tips"), QString::fromLocal8Bit("生成圆盘,直箭头和弯曲的箭头"));
    //测试圆盘
    float radius_circle = 0.5; //圆的半径
    int sectorCount_circle = 360; // 圆周上的点的数量
    QVector3D qv3d_circle(0.0f, 0.0f, 0.0f);
        
    createCircle(radius_circle, sectorCount_circle, qv3d_circle);

    //测试直箭头
    float radius_arrow = 1.0f;
    float height_arrow = 2.0f;
    int slices_arrow = 300;
    create_Arrow(radius_arrow, height_arrow, slices_arrow);
    
    //测试弯箭头
    float outerRadius = 1.0f;
    float innerRadius = 0.3f;
    int outerSegments = 100;
    int innerSegments = 50;
    create_Arrow_Curved(outerRadius, innerRadius, outerSegments, innerSegments);

}

void MainWindow::slotsShowSphere()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("显示球体和边界线"));
    m_foxOpenGLWidget->showSphereAndLine();

}


void MainWindow::slotsTest()
{
}

void MainWindow::slotsSetAlpha(int value)
{
    slots_statusbar_text_show(QString::fromLocal8Bit("使用着色器对模型的透明度进行更改"));
    float alpha = (float)(value) / 100;
    QString text = "value: " + QString::number(alpha, 'f', 2);
    m_sliderValue->setText(text);
    m_foxOpenGLWidget->setActorAlpha(alpha);
}

void MainWindow::slotsShow2DCrossSectionWidget()
{

    m_fox2DCrossSectionWidget->setWindowModality(Qt::NonModal);
    m_fox2DCrossSectionWidget->setWindowTitle("2D Cross Section");
    m_fox2DCrossSectionWidget->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
    m_fox2DCrossSectionWidget->show();


}

void MainWindow::slots_statusbar_text_show(QString text)
{
    ui->statusbar->showMessage(text);
}

void MainWindow::slotsOpenInvisalignData()
{

    slots_statusbar_text_show(QString::fromLocal8Bit("加载隐适美的病例"));
    //QString fileName_lower = ".\\caseData\\invisalignData\\DownArch\\m_CutGumPd0_0.stl";
    QString fileName_gum = ".\\caseData\\invisalignData\\DownArch\\m_CutGumPd0_14.stl";

    //m_foxOpenGLWidget->openMeshFilePath(fileName);
    QString folderPath = ".\\caseData\\invisalignData\\DownArch\\";
    QDir dir(folderPath);
    QStringList nameFilters;
    nameFilters << "*.stl";
    QStringList files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    QVector<QString> filePathList;
    for each (QString var in files)
    {
       QString filePath = folderPath +var;
       if (filePath.compare(fileName_gum) == 0) {
           continue;
       }
       filePathList.push_back(filePath);
    }
    m_foxOpenGLWidget->openMeshFilePath(filePathList, fileName_gum);
    updateAlphaSlider();


}

void MainWindow::slotsAbout()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("软件说明"));
    QMessageBox::aboutQt(nullptr, "About Qt");
}

void MainWindow::slotsCoordinate_System()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("在左下角添加坐标系"));
    //QMessageBox::information(nullptr, "Tips", QString::fromLocal8Bit("即将来袭,敬请期待..."));

    QString fileName_X = "../XTranslation.stl";
    QString fileName_Y = "../YTranslation.stl";
    QString fileName_Z = "../ZTranslation.stl";

    //就是右手坐标系的样子
    m_foxOpenGLWidget->openAttachmentFilePath(fileName_X, QVector3D(-60, -45, 0), QVector3D(1.0f,0.0f,0.0f));//red
    m_foxOpenGLWidget->openAttachmentFilePath(fileName_Y, QVector3D(-60, -45, 0), QVector3D(0.0f,1.0f,0.0f));//green
    m_foxOpenGLWidget->openAttachmentFilePath(fileName_Z, QVector3D(-60, -45, 0), QVector3D(0.0f,0.0f,1.0f));//blue

}

void MainWindow::slots_Change_to_Classic_mode()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("当前的旋转模式:ClassMode"));
    std::string Mode = "ClassMode";
    FoxOpenGLWidget::setRotateMode(Mode);
}

void MainWindow::slots_Change_to_ArcBall_mode()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("当前的旋转模式:ArcBallMode"));
    std::string Mode = "ArcBallMode";
    FoxOpenGLWidget::setRotateMode(Mode);
}

void MainWindow::slots_Change_to_Sphere_mode()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("当前的旋转模式:SphereMode"));
    std::string Mode = "SphereMode";
    FoxOpenGLWidget::setRotateMode(Mode);
}


void MainWindow::slots_Change_Add_Axis_2()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("使用qopengl直接绘制坐标系..."));

    emit opengl_Draw_coordinate_system_flag(QString("Enable_deep_testing"));
}
void MainWindow::slots_Change_Add_Axis_3()
{
    slots_statusbar_text_show(QString::fromLocal8Bit("使用qopengl直接绘制坐标系..."));

    emit opengl_Draw_coordinate_system_flag(QString("Prohibit_deep_testing"));
}

void MainWindow::slots_Change_GridMode_EnableDeepTesting()
{
    emit Change_GridMode(QString("EnableDeepTesting"));
}

void MainWindow::slots_Change_GridMode_ProhibitDeepTesting()
{
    emit Change_GridMode(QString("ProhibitDeepTesting"));
}

void MainWindow::initAlphaSlider()
{
    m_sliderValue = new QLabel(this);
    m_sliderValue->setText("value: 0.00");
    m_sliderValue->setGeometry(width() - 255, 60, 100, 15);


    m_setAlphaSlider = new QSlider(Qt::Horizontal, this);
    // 设置最大值 最小值 步长
    int max = 100;
    int min = 0;
    int step = 10;
    m_setAlphaSlider->setMaximum(max);
    m_setAlphaSlider->setMinimum(min);
    m_setAlphaSlider->setSingleStep(step);

    // 设置位置 高宽
    m_setAlphaSlider->setGeometry(width() - 170, 60, 150, 15);

    // 设置显示最上层
    m_setAlphaSlider->raise();

}

void MainWindow::updateAlphaSlider()
{
    m_setAlphaSlider->setValue(100);
    QString text = "value: 100";
    m_sliderValue->setText(text);
}
