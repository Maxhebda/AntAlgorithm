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
    showAcceleration=0;
    ui->menu->setEnabled(false);
    connect(&timer,SIGNAL(timeout()),this,SLOT(step()));
    timer.setInterval(1);
    connect(ui->actionStart,SIGNAL(triggered()),this,SLOT(clickStart()));
    connect(ui->actionStop,SIGNAL(triggered()),this,SLOT(clickStop()));
    connect(ui->actionReset,SIGNAL(triggered()),this,SLOT(clickReset()));

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

    // -- add one ant --
    Ant ant(255);
    ant.setColor(150);
    ant.setX(450);
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
    ui->menu->setTitle(mySprintf("Krok=%d",counterStep));

    // --- rysuj tylko co okreslona liczbe cykli np co 20 cykli
    showAcceleration++;
    if (showAcceleration==SHOWaCCELERATION)
    {
        showAcceleration=0;
        showBoard();
    }
}

void MainWindow::clickStart()
{
    timer.start();
}

void MainWindow::clickStop()
{
    timer.stop();
}

void MainWindow::clickReset()
{
    board->clear();
    counterStep=0;
}
