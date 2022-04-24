#ifndef NOTBOOK_H
#define NOTBOOK_H
//Подключение классов базы данных
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QListWidgetItem>
/////////////////////
#include <QDialog>

namespace Ui {
class NotBook;
}

class NotBook : public QDialog
{
    Q_OBJECT

public:
    explicit NotBook(QWidget *parent = nullptr);
    ~NotBook();

private slots:
    void on_button_creat_clicked();

    void on_button_remove_clicked();

private:
    Ui::NotBook *ui;
    //связь окон
   // MainWindow *main_window;
    // база данных
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;

    QString topic;
    QString content;
    int save_topic_pk;

public slots:
    void slot();
    void slot_listWidget(int topic_pk);

signals:
    void signalNote(QString);
    void buttonRemove();

};

#endif // NOTBOOK_H


