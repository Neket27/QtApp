#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculator.h"
#include "image.h"
#include "mypainter.h"
#include <QMessageBox>
#include <QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    window_paint=new MyPainter(this);
    note_book=new NotBook(this);
    window_calculator=new calculator(this);
    //подключение взаимодействия двух окон
    connect( this, &MainWindow::signal,note_book,&NotBook::slot);
    connect( this, &MainWindow::signal_listWidget,note_book,&NotBook::slot_listWidget);

    connect(note_book,&NotBook::signalNote, this, &MainWindow::slotNote);
    connect(note_book,&NotBook::buttonRemove,this,&MainWindow::slotbuttonRemove);
    ////////////
    ui->setupUi(this);


    db= QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB.db");
    if(db.open()){
        qDebug("open");
    }else{
        qDebug("no open");
    }
   QString maxS;
    query = new QSqlQuery(db);
    query->prepare("SELECT  *FROM Table_topic");
    query->exec();

    while (query->next()) {

            maxS = query->value(1).toString();
            ui-> listWidget->addItem(maxS);
        //ui-> listWidget->addItem(maxS);
    }
    // ui-> listWidget->addItem(maxS);
    ui->label_2->setText(maxS);
     qDebug() <<"d1: " <<query->value(1).toString();
    query-> exec("CREATE TABLE Table_topic(id INT, topic TEXT, content TEXT);");

    model =new QSqlQueryModel();
   // model->setQuery("SELECT topic FROM Table_topic WHERE id IN(2)");

     model->setQuery("SELECT *FROM `Table_topic`");


    ui->tableView-> setModel(model);

    ui-> listWidget->addItem("Audi");


//    query->prepare("INSERT INTO TABLE");
//    qDebug() <<"d2: " <<query->value(1).toString();
//    //qDebug() <<"out: " << model->index(1,0,1);
//    if (query->isActive()){

//        qDebug("Запрос сработал");
//               query->first();
//                qDebug() <<"dd: " << query->value(2).toString();
//               //FillForm();
//           } else {
//               qDebug("Облом");

//           }
  }


MainWindow::~MainWindow()
{
    delete ui;
}

//создание новой заметки
void MainWindow::on_add_notbook_triggered()
{

    note_book->show();

   // NotBook my_window;

     //  my_window.setModal(true);
     //  my_window.exec();
}

void MainWindow::on_pushButton_5_clicked()
{
    model->insertRow(model->rowCount());
    // emit работа по сигналу
    emit signal();
    //itm= new QListWidgetItem();

    //QMessageBox::warning(this,"warning",itm->text());
}

void MainWindow::slotNote(QString form_note)
{
    ui->label->setText(form_note);
    model =new QSqlQueryModel();
   // model->setQuery("SELECT topic FROM Table_topic WHERE id IN(2)");

     model->setQuery("SELECT *FROM `Table_topic`");
     ui->tableView-> setModel(model);

     QString maxS;
      query = new QSqlQuery(db);
      query->prepare("SELECT  *FROM Table_topic");
      query->exec();
        ui->listWidget->clear();
      while (query->next()) {

              maxS = query->value(1).toString();
              ui-> listWidget->addItem(maxS);
          //ui-> listWidget->addItem(maxS);
      }
}

void MainWindow::slotbuttonRemove()
{
    //model-> removeRow(currentRow);//удаление строки с базы данных
  //   model->select();//обновление базы данных

    model =new QSqlQueryModel();
   // model->setQuery("SELECT topic FROM Table_topic WHERE id IN(2)");

     model->setQuery("SELECT *FROM `Table_topic`");


    ui->tableView-> setModel(model);

     qDebug("Update");


     QString maxS;
      query = new QSqlQuery(db);//считываем значения с базы данных
      query->prepare("SELECT  *FROM Table_topic");// берем таблицу из базы данных которая называется Table_topic
      query->exec();//инициализируем записи
        ui->listWidget->clear();
      while (query->next()) {

              maxS = query->value(1).toString();
              ui-> listWidget->addItem(maxS);
          //ui-> listWidget->addItem(maxS);
      }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow=index.row();
    qDebug("index");
}

void MainWindow::on_button_calculator_clicked()
{
    //calculator my_window;

       // my_window.setModal(true);
       // my_window.exec();
         window_calculator->show();
}


//  двойной клик по listWidget
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //item->setBackground(QColor(0,0,255));
    QListWidgetItem *itm=ui->listWidget->currentItem();
   // itm->setBackground(QColor(0,0,255));

    qDebug() <<"used";
    int topic_var;
     query = new QSqlQuery(db);
     query->prepare("SELECT  *FROM Table_topic");
     query->exec();
int i=0;
    while (query->next()) {

            if (selected==i){
            topic_var = query->value(0).toInt();//беру айди записи
            qDebug() <<"topic_varrr: "<<topic_var;

             emit signal_listWidget(topic_var);


            }
            i++;
           // ui-> listWidget->addItem(maxS);
        //ui-> listWidget->addItem(maxS);
    }


  //  while (query->next()){
//    int i=0;
//    if (i==selected){

//        QListWidgetItem *it= ui->listWidget->takeItem(selected);
//        qDebug() <<"topic_var: "<<it;
//    }
//        i++;

   // }
    // qDebug() <<"topic_var: "<<it;
     note_book->show();
}
//узнаём номер нажатой строки в listWidget
void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    selected=currentRow;
}

void MainWindow::on_button_image_clicked()
{
    image image_window;

            image_window.setModal(true);
            image_window.exec();
}

void MainWindow::on_button_paint_clicked()
{

    window_paint->show();
//    MyPainter paint_window;
//            paint_window.setModal(true);
//            paint_window.exec();
}

void MainWindow::on_button_notebook_clicked()
{
    note_book->show();
}
