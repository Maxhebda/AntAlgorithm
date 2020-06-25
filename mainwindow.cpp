#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counterStep=0;
        connect(&timer,SIGNAL(timeout()),this,SLOT(step()));
        timer.setInterval(10);
    connect(ui->actionStart,SIGNAL(triggered()),this,SLOT(clickStart()));
    connect(ui->actionStop,SIGNAL(triggered()),this,SLOT(clickStop()));

    QWidget::setMinimumHeight(700+20+ui->menubar->height());
    QWidget::setMaximumHeight(700+20+ui->menubar->height());
    image = new QImage(900,700,QImage::Format_RGB32);
    image -> fill(QColor(0,0,0));
    paintOnImage = new QPainter;
    paintOnImage->begin(image);

    board.clear();
    board.set(20,20,255);
    Ant ant(255);
    ant.setX(500);
    ant.setY(500);
    board.addAnt(ant);
    ant.setX(510);
    ant.setY(500);
    board.addAnt(ant);
    showBoard();
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

void MainWindow::showBoard()
{
    for (unsigned short int y=0;y<700; y++)
    {
        for(unsigned short int x=0;x<900;x++)
        {
            unsigned short int floorColor = board.get(y,x);
            paintOnImage->setPen(QColor(floorColor,floorColor,floorColor));
            paintOnImage->drawPoint(x,y);
        }
    }

    for (unsigned short int index = 0; index < board.getAnts().size(); index ++)
    {
        paintOnImage->setPen(QColor(0,255,0));
        paintOnImage->drawPoint(board.getAnt(index).getX(),board.getAnt(index).getY());
    }
    repaint();
}

void MainWindow::step()
{
    counterStep++;
    board.goNextStep();
    ui->menuStart->setTitle(QVariant(counterStep).toString());
    showBoard();
}

void MainWindow::clickStart()
{
    timer.start();
}

void MainWindow::clickStop()
{
    timer.stop();
}
