#include "mypainter.h"
#include "ui_mypainter.h"


MyPainter::MyPainter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyPainter)
{
   ui->setupUi(this);

    scene = new paintScene();       // Инициализируем графическую сцену
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену

    timer = new QTimer();       // Инициализируем таймер
    connect(timer, &QTimer::timeout, this, &MyPainter::slotTimer);
    timer->start(100);          // Запускаем таймер
}

MyPainter::~MyPainter()
{
    delete ui;
}

void MyPainter::slotTimer()
{
    /* Переопределяем размеры графической сцены в зависимости
     * от размеров окна
     * */
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void MyPainter::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}
