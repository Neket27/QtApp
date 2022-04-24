#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "notbook.h"
#include "calculator.h"
#include "mypainter.h";
//Подключение классов базы данных
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
//#include <QSqlTableModel>
#include<QSqlQueryModel>
/////////////////////
#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_add_notbook_triggered();

    void on_pushButton_5_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_button_calculator_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_currentRowChanged(int currentRow);

    void on_button_image_clicked();

    void on_button_paint_clicked();

    void on_button_notebook_clicked();

private:
    Ui::MainWindow *ui;
    //второе окно
    NotBook *note_book;
    calculator *window_calculator;
    MyPainter *window_paint;
    // база данных
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlQueryModel *model;
    QListWidgetItem *itm;
    int selected;
   // QSqlTableModel *model;
    int currentRow;

public slots:
    void slotNote(QString form_note);
    void slotbuttonRemove();
    //соединение двух окон
signals:
   void signal();
   void signal_listWidget(int);


};
#endif // MAINWINDOW_H
