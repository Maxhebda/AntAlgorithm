#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QString>

// QString mySprintf(format, arguments);
// use: s = mySprintf("Its %d %s .",12,"May");
//      s = "12 May .";
template<typename ... Args>
QString mySprintf(const char * format,Args ... a)
{
    char scream[255];
    sprintf(scream,format,a ...);
    return scream;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counterStep=0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(step()));
    timer.setInterval(5);
    connect(ui->actionStart,SIGNAL(triggered()),this,SLOT(clickStart()));
    connect(ui->actionStop,SIGNAL(triggered()),this,SLOT(clickStop()));

    QWidget::setMinimumHeight(700+20+ui->menubar->height());
    QWidget::setMaximumHeight(700+20+ui->menubar->height());
    image = new QImage(900,700,QImage::Format_RGB32);
    image -> fill(QColor(0,0,0));
    paintOnImage = new QPainter;
    paintOnImage->begin(image);

    board = new Board();
    oldBoard = new Board();
    board->clear();
    oldBoard->clear();

    // -- add 2 ant --
    Ant ant(255);
    ant.setX(460);
    ant.setY(350);
    board->addAnt(ant);
    ant.setColor(150);
    ant.setX(440);
    ant.setY(350);
    board->addAnt(ant);
}

MainWindow::~MainWindow()
{
    delete ui;
    paintOnImage->end();
    delete image;
    delete board;
    delete oldBoard;
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
            if (board->get(y,x)!=oldBoard->get(y,x))
            {
                unsigned short int floorColor = board->get(y,x);
                paintOnImage->setPen(QColor(floorColor,floorColor,floorColor));
                paintOnImage->drawPoint(x,y);
                // aktualizacja starej planszy po zmianach nowej
                oldBoard->set(y,x,floorColor);
            }
        }
    }
    //    // --- rysowanie mrowki ---
    //    for (unsigned short int index = 0; index < board->getAnts().size(); index ++)
    //    {
    //        paintOnImage->setPen(QColor(0,255,0));
    //        paintOnImage->drawPoint(board->getAnt(index).getX(),board->getAnt(index).getY());
    //    }
    repaint();
}

void MainWindow::step()
{
    counterStep++;
    board->goNextStep();
    ui->menuStart->setTitle(mySprintf("Start Krok=%d",counterStep));
//    ui->menuStart->setTitle(mySprintf("(%d,%d tlo=%d kierunek=%d",board->getAnt(0).getX(),board->getAnt(0).getY(),board->get(board->getAnt(0).getX(),board->getAnt(0).getY()),board->getAnt(0).getDirection()));
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
