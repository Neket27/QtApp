#include "notbook.h"
#include "ui_notbook.h"
#include "mainwindow.h"
NotBook::NotBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotBook)
{


    db= QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB.db");
    if(db.open()){
        qDebug("open");
    }else{
        qDebug("no open");
    }
    query = new QSqlQuery(db);
    query-> exec("CREATE TABLE TelephoneBook(Firstname TEXT,LastName TEXT, Telephone INT);");

    model =new QSqlTableModel(this,db);
    model->setTable("TelephoneBook");
    model->select();
    //ui->tableView-> setModel(model);
   // main_window = new MainWindow;





    ui->setupUi(this);
}

NotBook::~NotBook()
{
    delete ui;
}

void NotBook::on_button_creat_clicked()
{

   // model->insertRow(model->rowCount());
    qDebug("Clicked");
    QString maxS;
     query = new QSqlQuery(db);
    // query->prepare("SELECT  *FROM Table_topic");111111111111111111111111111111111111111111111
    // query->prepare("DELETE FROM Table_topic WHERE id = ?");111111111111111111111111111111
    // query->prepare("delete from Table_topic where (ID = "+QString::number(save_topic_pk)+")");
     //query->exec();
     if (save_topic_pk==-1){
         save_topic_pk=int (rand());
     }
   query->prepare("delete from Table_topic where (ID = "+QString::number(save_topic_pk)+")");//НЕ Срабатывает
   query->exec();
     query->prepare("INSERT INTO Table_topic (id,topic,content)" "VALUES (:id,:topic,:content)");
          query->bindValue(":id", save_topic_pk);
          query->bindValue(":topic", ui->topic->text());
          query->bindValue(":content", ui->content->toPlainText());

          query->exec();

     while(query->next()){
      if(save_topic_pk==query->value(0).toInt()){

            query->value(1).data();
            query->exec();
      }
     }

    save_topic_pk=-1;
    emit signalNote(ui->topic->text());
    ui->topic->clear();
    ui->content->clear();

}

void NotBook::slot()
{
    ui->label->setText("signal");

}

void NotBook::slot_listWidget(int(topic_pk))
{
    save_topic_pk=topic_pk;
    //база данных
    query = new QSqlQuery(db);
    query->prepare("SELECT  *FROM Table_topic");
    query->exec();



qDebug()<<"topic_pk: "<<topic_pk;
   while(query->next()){
    if(topic_pk==query->value(0).toInt()){
    topic =query->value(1).toString();
    content =query->value(2).toString();
    ui->topic->setText(topic);
    ui->content->setText(content);
    }

  }
    QString k=QString::number(topic_pk);
    //ui->label->setText(k);


}
//удаление в базе данных
void NotBook::on_button_remove_clicked()
{
  emit buttonRemove();
    qDebug("buttonRemove");
    query->prepare("delete from Table_topic where (ID = "+QString::number(save_topic_pk)+")");
     query->exec();

}
