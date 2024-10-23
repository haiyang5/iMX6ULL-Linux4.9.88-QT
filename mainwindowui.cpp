#include "mainwindow.h"

#include "commonhelper.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    initUi();
    initCtrl();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUi()
{
    m_pSliderWidget->addWidget(initPage1());
    m_pSliderWidget->addWidget(initPage2());

    auto *pLayout = new QVBoxLayout;                //垂直布局，布局顺序为添加顺序
    pLayout->addWidget(m_pTopWidget,    0);         //第二个参数为拉伸因子，数值越大，自动拉伸的越大
    pLayout->addWidget(m_pSliderWidget, 1);
    pLayout->setSpacing(0);                         //设置间距
    pLayout->setMargin(0);                          //设置边缘空隙
    setLayout(pLayout);
    setObjectName("mainwindow");
    setFixedSize(m_screenWidth, m_screenHeigh);
    setBackground(QPixmap(":/misc/resource/image/background.jpg"));
    setCursor(QCursor(QPixmap(":/misc/resource/image/point.png"), -1, -1));      //设置鼠标样式
}

void MainWindow::setBackground(const QPixmap &pixmap)
{
    QPalette  palette = this->palette();
    palette.setBrush(backgroundRole(), pixmap.scaled(m_screenWidth, m_screenHeigh, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setPalette(palette);
    setAutoFillBackground(true);
}

QWidget *MainWindow::initPage1()
{
    auto ret = new QWidget(this);

    auto pSystemBtn = createButton("系统", "systemBtn");
    pSystemBtn->setStyleSheet("image: url(:/misc/resource/image/system.png);");
    connect(pSystemBtn, &QPushButton::clicked, this, &MainWindow::systemBtnClicked);

    auto pCalculatorBtn = createButton("计算器", "calculatorBtn");
    pCalculatorBtn->setStyleSheet("image: url(:/misc/resource/image/calculator.png);");
    connect(pCalculatorBtn, &QPushButton::clicked, this, &MainWindow::calculatorBtnClicked);

    auto pMusicBtn = createButton("音乐", "musicBtn");
    pMusicBtn->setStyleSheet("image: url(:/misc/resource/image/music.png);");
    connect(pMusicBtn, &QPushButton::clicked, this, &MainWindow::musicBtnClicked);

    auto pVideoBtn = createButton("视频", "videoBtn");
    pVideoBtn->setStyleSheet("image: url(:/misc/resource/image/video.png);");
    connect(pVideoBtn, &QPushButton::clicked, this, &MainWindow::videoBtnClicked);

    auto pWeatherBtn = createButton("天气", "weatherBtn");
    pWeatherBtn->setStyleSheet("image: url(:/misc/resource/image/weather.png);");
    connect(pWeatherBtn, &QPushButton::clicked, this, &MainWindow::weatherBtnClicked);

    auto pMapBtn = createButton("在线地图", "mapBtn");
    pMapBtn->setStyleSheet("image: url(:/misc/resource/image/map.png);");
    connect(pMapBtn, &QPushButton::clicked, this, &MainWindow::mapBtnClicked);

    auto pRecorderBtn = createButton("录音机", "recorderBtn");
    pRecorderBtn->setStyleSheet("image: url(:/misc/resource/image/recorder.png);");
    connect(pRecorderBtn, &QPushButton::clicked, this, &MainWindow::recorderBtnClicked);



    auto pLayout = new QGridLayout;                     //网格布局，每个按钮布局在对应的网格坐标
    pLayout->addWidget(pMusicBtn,               0, 0);
    pLayout->addWidget(pVideoBtn,               0, 1);
    pLayout->addWidget(pWeatherBtn,             0, 2);
    pLayout->addWidget(pMapBtn,                 0, 3);
    pLayout->addWidget(pSystemBtn,              0, 4);
    pLayout->addWidget(pCalculatorBtn,          0, 5);
    pLayout->setContentsMargins(20, 0, 20, 0);          //设置整体内容与left, top, right, bottom边缘间隙
    pLayout->setVerticalSpacing(30);                    //设置控件之间的垂直间隙

    auto pVLayout = new QVBoxLayout;
    pVLayout->addLayout(pLayout);                       //直接使用网格布局会出错
    pVLayout->addStretch();                             //布局的末尾添加一个可拉伸空间，其最小尺寸和拉伸因子均为零
    pVLayout->setSpacing(0);
    pVLayout->setMargin(0);

    ret->setFixedWidth(m_screenWidth);
    ret->setLayout(pVLayout);

    return ret;
}

QWidget *MainWindow::initPage2()
{
//    auto pOLEDBtn = createButton("OLED", "OLEDBtn");
//    pOLEDBtn->setStyleSheet("image: url(:/misc/resource/image/oled.png);");
//    connect(pOLEDBtn, &QPushButton::clicked, this, &MainWindow::oledBtnClicked);

//    auto pRemoteControlBtn = createButton("遥控器", "remoteControlBtn");
//    pRemoteControlBtn->setStyleSheet("image: url(:/misc/resource/image/remotecontrol.png);");
//    connect(pRemoteControlBtn, &QPushButton::clicked, this, &MainWindow::remoteCtrlBtnClicked);

//    auto pUltrasonicWaveBtn = createButton("超声波", "ultrasonicWaveBtn");
//    pUltrasonicWaveBtn->setStyleSheet("image: url(:/misc/resource/image/ultrasonicwave.png);");
//    connect(pUltrasonicWaveBtn, &QPushButton::clicked, this, &MainWindow::ultrasonicwaveBtnClicked);

//    auto pPhotosensitiveBtn = createButton("光敏", "photosensitiveBtn");
//    pPhotosensitiveBtn->setStyleSheet("image: url(:/misc/resource/image/photosensitive.png);");
//    connect(pPhotosensitiveBtn, &QPushButton::clicked, this, &MainWindow::photosensitiveBtnClicked);

//    auto pInfraredBtn = createButton("热红外", "infraredBtn");
//    pInfraredBtn->setStyleSheet("image: url(:/misc/resource/image/infrared.png);");
//    connect(pInfraredBtn, &QPushButton::clicked, this, &MainWindow::infraredBtnClicked);

//    auto pIlluminationBtn = createButton("光照", "illuminationBtn");
//    pIlluminationBtn->setStyleSheet("image: url(:/misc/resource/image/illumination.png);");
//    connect(pIlluminationBtn, &QPushButton::clicked, this, &MainWindow::illuminationBtnClicked);

//    auto pKeyBtn = createButton("按键", "keyBtn");
//    pKeyBtn->setStyleSheet("image: url(:/misc/resource/image/key.png);");
//    connect(pKeyBtn, &QPushButton::clicked, this, &MainWindow::keyBtnClicked);

//    auto pElectricityBtn = createButton("DAC", "electricityBtn");
//    pElectricityBtn->setStyleSheet("image: url(:/misc/resource/image/electricity.png);");
//    connect(pElectricityBtn, &QPushButton::clicked, this, &MainWindow::electricityBtnClicked);

//    auto backlightBtn = createButton("背光", "backlightBtn");
//    backlightBtn->setStyleSheet("image: url(:/misc/resource/image/backlight.png);");
//    connect(backlightBtn, &QPushButton::clicked, this, &MainWindow::backlightBtnClicked);

//    auto pTemperatureBtn = createButton("温湿度", "temperatureBtn");
//    pTemperatureBtn->setStyleSheet("image: url(:/misc/resource/image/temperature.png);");
//    connect(pTemperatureBtn, &QPushButton::clicked, this, &MainWindow::temperatureBtnClicked);


    auto pCameraBtn = createButton("倒车监测", "cameraBtn", this);
    pCameraBtn->setStyleSheet("image: url(:/misc/resource/image/camera.png);");
    connect(pCameraBtn, &QPushButton::clicked, this, &MainWindow::cameraBtnClicked);

    auto pTemperatureBtn = createButton("温湿度", "temperatureBtn");
    pTemperatureBtn->setStyleSheet("image: url(:/misc/resource/image/temperature.png);");
    connect(pTemperatureBtn, &QPushButton::clicked, this, &MainWindow::temperatureBtnClicked);

    auto pIlluminationBtn = createButton("光照", "illuminationBtn");
    pIlluminationBtn->setStyleSheet("image: url(:/misc/resource/image/illumination.png);");
    connect(pIlluminationBtn, &QPushButton::clicked, this, &MainWindow::illuminationBtnClicked);

    auto backlightBtn = createButton("背光", "backlightBtn");
    backlightBtn->setStyleSheet("image: url(:/misc/resource/image/backlight.png);");
    connect(backlightBtn, &QPushButton::clicked, this, &MainWindow::backlightBtnClicked);

    auto pElectricityBtn = createButton("灯光", "electricityBtn");
    pElectricityBtn->setStyleSheet("image: url(:/misc/resource/image/electricity.png);");
    connect(pElectricityBtn, &QPushButton::clicked, this, &MainWindow::electricityBtnClicked);

    auto pUltrasonicWaveBtn = createButton("距离", "ultrasonicWaveBtn");
    pUltrasonicWaveBtn->setStyleSheet("image: url(:/misc/resource/image/ultrasonicwave.png);");
    connect(pUltrasonicWaveBtn, &QPushButton::clicked, this, &MainWindow::ultrasonicwaveBtnClicked);

    auto ret = new QWidget(this);
    auto pLayout = new QGridLayout;

    pLayout->addWidget(pCameraBtn,              0, 0);
    pLayout->addWidget(pTemperatureBtn,         0, 1);
    pLayout->addWidget(pIlluminationBtn,        0, 2);
    pLayout->addWidget(backlightBtn,            0, 3);
    pLayout->addWidget(pElectricityBtn,         0, 4);
    pLayout->addWidget(pUltrasonicWaveBtn,      0, 5);

//    pLayout->addWidget(pOLEDBtn,           0, 0);
//    pLayout->addWidget(pRemoteControlBtn,  0, 1);
//    pLayout->addWidget(pUltrasonicWaveBtn, 0, 2);
//    pLayout->addWidget(pPhotosensitiveBtn, 0, 3);
//    pLayout->addWidget(pElectricityBtn,    0, 4);
//    pLayout->addWidget(pInfraredBtn,       0, 5);
//    pLayout->addWidget(pIlluminationBtn,   1, 0);
//    pLayout->addWidget(pKeyBtn,            1, 1);
//    pLayout->addWidget(backlightBtn,       1, 2);
//    pLayout->addWidget(pTemperatureBtn,    1, 3);
    pLayout->setContentsMargins(20, 0, 20, 0);
    pLayout->setVerticalSpacing(10);

    auto pVLayout = new QVBoxLayout;
    pVLayout->addLayout(pLayout);
    pVLayout->addStretch();
    pVLayout->setSpacing(0);
    pVLayout->setMargin(0);

    ret->setFixedWidth(m_screenWidth);
    ret->setLayout(pVLayout);

    return ret;
}

QPushButton *MainWindow::createButton(const QString &text, const QString& objName, QWidget *parent)
{
    auto ret = new QPushButton(text, parent);

    ret->setObjectName(objName);

    return ret;
}


