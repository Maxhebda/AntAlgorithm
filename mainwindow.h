#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QtGui>
#include <QtCore>
#include <ant.h>
#include <board.h>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showBoard();

private:
    Ui::MainWindow *ui;
    QImage * image;
    QPainter * paintOnImage;
    Board * board;
    Board * oldBoard;
    QTimer timer;
    int counterStep;

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void step();
    void clickStart();
    void clickStop();
};
#endif // MAINWINDOW_H
