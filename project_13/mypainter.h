#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QDialog>

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>

#include <paintscene.h>

namespace Ui {
class MyPainter;
}

class MyPainter : public QDialog
{
    Q_OBJECT

public:
    explicit MyPainter(QWidget *parent = 0);
    ~MyPainter();

private:
    Ui::MyPainter *ui;
    QTimer *timer;      /* Определяем таймер для подготовки актуальных размеров
                         * графической сцены
                         * */
    paintScene *scene;  // Объявляем кастомную графическую сцену

private:
    /* Переопределяем событие изменения размера окна
     * для пересчёта размеров графической сцены
     * */
    void resizeEvent(QResizeEvent * event);

private slots:
    void slotTimer();
};

#endif // MYPAINTER_H
