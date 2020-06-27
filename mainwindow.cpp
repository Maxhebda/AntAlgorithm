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
    srand(time(NULL));
    ui->setupUi(this);
    counterStep=0;
    showAcceleration=0;
    ui->menu->setEnabled(false);
    connect(&timer,SIGNAL(timeout()),this,SLOT(step()));
    timer.setInterval(1);
    connect(ui->actionStart,SIGNAL(triggered()),this,SLOT(clickStart()));
    connect(ui->actionStop,SIGNAL(triggered()),this,SLOT(clickStop()));
    connect(ui->actionReset,SIGNAL(triggered()),this,SLOT(clickReset()));
    connect(ui->actionDodaj,SIGNAL(triggered()),this,SLOT(clickDodaj()));
    connect(ui->actionUsu,SIGNAL(triggered()),this,SLOT(clickUsun()));

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
    Ant ant(rand()%10+1);
    ant.setX(225);
    ant.setY(175);
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

void MainWindow::mySetPen(unsigned short int Color)
{
                    switch (Color) {
                        case 0 : {paintOnImage->setPen(QColor(0,0,0));break;}
                        case 1 : {paintOnImage->setPen(QColor(0,255,255));break;}
                        case 2 : {paintOnImage->setPen(QColor(255,0,255));break;}
                        case 3 : {paintOnImage->setPen(QColor(255,255,0));break;}
                        case 4 : {paintOnImage->setPen(QColor(0,0,255));break;}
                        case 5 : {paintOnImage->setPen(QColor(0,255,0));break;}
                        case 6 : {paintOnImage->setPen(QColor(255,0,100));break;}
                        case 7 : {paintOnImage->setPen(QColor(120,255,120));break;}
                        case 8 : {paintOnImage->setPen(QColor(120,120,255));break;}
                        case 9 : {paintOnImage->setPen(QColor(255,100,100));break;}
                        case 10 : {paintOnImage->setPen(QColor(0,100,255));break;}
                        default: paintOnImage->setPen(QColor(255,255,255));
                    }
}

void MainWindow::myDrawPoint(unsigned short x, unsigned short y)
{
paintOnImage->drawPoint(x*2,y*2);
paintOnImage->drawPoint(x*2+1,y*2);
paintOnImage->drawPoint(x*2,y*2+1);
paintOnImage->drawPoint(x*2+1,y*2+1);
}

void MainWindow::showBoard()
{
//    for (unsigned short int y=0;y<350; y++)
//    {
//        for(unsigned short int x=0;x<450;x++)
//        {
//            if (board->get(y,x)!=oldBoard->get(y,x))
//            {
//                unsigned short int floorColor = board->get(y,x);
//                switch (floorColor) {
//                    case 0 : {paintOnImage->setPen(QColor(0,0,0));break;}
//                    case 1 : {paintOnImage->setPen(QColor(0,255,255));break;}
//                    case 2 : {paintOnImage->setPen(QColor(255,0,255));break;}
//                    case 3 : {paintOnImage->setPen(QColor(255,255,0));break;}
//                    case 4 : {paintOnImage->setPen(QColor(0,0,255));break;}
//                    case 5 : {paintOnImage->setPen(QColor(0,255,0));break;}
//                    case 6 : {paintOnImage->setPen(QColor(255,0,100));break;}
//                    case 7 : {paintOnImage->setPen(QColor(120,255,120));break;}
//                    case 8 : {paintOnImage->setPen(QColor(120,120,255));break;}
//                    case 9 : {paintOnImage->setPen(QColor(255,100,100));break;}
//                    case 10 : {paintOnImage->setPen(QColor(0,100,255));break;}
//                    default: paintOnImage->setPen(QColor(255,255,255));
//                }
//                paintOnImage->drawPoint(x*2,y*2);
//                paintOnImage->drawPoint(x*2+1,y*2);
//                paintOnImage->drawPoint(x*2,y*2+1);
//                paintOnImage->drawPoint(x*2+1,y*2+1);
//                // aktualizacja starej planszy po zmianach nowej
//                oldBoard->set(y,x,floorColor);

//            }
//        }
//    }
        // --- rysowanie mrowki ---
        for (unsigned short int index = 0; index < board->getAnts().size(); index ++)
        {
            mySetPen(board->getAnt(index).getColor());
            myDrawPoint(board->getAnt(index).getX(),board->getAnt(index).getY());
        }
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
    ui->actionStart->setEnabled(false);
    ui->actionStop->setEnabled(true);
}

void MainWindow::clickStop()
{
    timer.stop();
    ui->actionStart->setEnabled(true);
    ui->actionStop->setEnabled(false);
}

void MainWindow::clickReset()
{
    board->clear();
    counterStep=0;
}

void MainWindow::clickDodaj()
{
    if (board->getAnts().size()<30)
    {
        Ant ant(rand()%10+1);
        ant.setDirection(rand()%4);
        ant.setX(rand()%430+10);
        ant.setY(rand()%330+10);
        board->addAnt(ant);
        ui->menuMrowek->setTitle(mySprintf("Mrówek = %d",board->getAnts().size()));
    }
}

void MainWindow::clickUsun()
{
    if (board->getAnts().size()>1)
    {
        board->deleteAnt(0);
        ui->menuMrowek->setTitle(mySprintf("Mrówek = %d",board->getAnts().size()));
    }
}
