#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mMaximized = false;

    //test = new QSizeGrip(this);
    //test->resize(10,10);
    //test->setGeometry(20,20,20,20);
    //ui->verticalLayout_6->addWidget(test);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(minimized()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(restore_maximized()));
    connect(ui->pushButton_3, &QPushButton::clicked, this, &QApplication::quit);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::minimized()
{
    MainWindow::setWindowState(Qt::WindowMinimized);
    MainWindow::showMinimized();
}

void MainWindow::restore_maximized()
{
    if(mMaximized == false)
    {
        MainWindow::setWindowState(Qt::WindowFullScreen);
        ui->drop_shadow_layout->setContentsMargins(0,0,0,0); //Pour le vrai full screen //drop_shadow_layout c'est le nom du layout de central widget
        ui->drop_shadow_frame->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 44, 111, 255), stop:0.521368 rgba(28, 29, 73, 255)); border-radius: 0px;");
        mMaximized = true;
    }
    else
    {
        MainWindow::setWindowState(Qt::WindowNoState);
        ui->drop_shadow_layout->setContentsMargins(0,0,0,0); //Sur macos
        ui->drop_shadow_frame->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(42, 44, 111, 255), stop:0.521368 rgba(28, 29, 73, 255)); border-radius: 12px;");
        //test->setGeometry(20,20,20,20);
        mMaximized = false;
    }
    qDebug() << "After : " << mMaximized;
}

/*MOOVING*/
/*mMaximized == false car sinon si on bouge la fenêtre quand elle est en full screen cela fait bugué le retour au normal state*/
void MainWindow::mousePressEvent(QMouseEvent* event)
{
  if(ui->title_bar->underMouse() && event->button() == Qt::LeftButton && mMaximized == false)
  {
    mMoving = true;
    mLastMousePosition = event->pos();
  }

  if(ui->frame_2->underMouse() && event->button() == Qt::LeftButton)
  {
    qDebug() << "UwU";
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{

  if(event->buttons().testFlag(Qt::LeftButton) && mMoving)
  {
    this->move(this->pos() + (event->pos() - mLastMousePosition));
  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

