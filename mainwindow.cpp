#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setMinimumHeight(700+20+ui->menubar->height());
    QWidget::setMaximumHeight(700+20+ui->menubar->height());
    image = new QImage(900,700,QImage::Format_RGB32);
    image -> fill(QColor(0,0,0));
    paintOnImage = new QPainter;
    paintOnImage->begin(image);
}

MainWindow::~MainWindow()
{
    delete ui;
    paintOnImage->end();
    delete image;
    delete paintOnImage;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(10,10 + ui->menubar->height(),*image);
    painter.end();
}
