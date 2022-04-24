#include "image.h"
#include "ui_image.h"

#include <QDebug>
#include <QtWidgets/QFileDialog>
#include <QDial>
#include <QPainter>
#include <QListWidgetItem>
#include <QIcon>




image::image(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::image)
{
    ui->setupUi(this);

   }

image::~image()
{
    delete ui;
}


QVector<QFileInfo> image:: listfilesindir(QString path)
{


    QStringList filtr;
    QString line="";
    QDir dir(path);
    filtr << "" << "*.jpg" << "*.png";
    bool ok = dir.exists();
    if (ok)
    {
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Name);
        dir.setNameFilters(filtr);
        QFileInfoList list = dir.entryInfoList();

        for (int i = 0; i < list.size(); ++i)
        {
            QFileInfo fileInfo = list.at(i);
           // line+=fileInfo.fileName()+"  ";

            vtr.append(fileInfo);

        }
    }
    int i = 0;
    while (vtr.size()!=i){

          qInfo()<<"vtr= "<<vtr[i];
 i++;
    }

return vtr;

}


void image::on_button_load_clicked()
{
     QPixmap pix_list;
        auto folder_path=QFileDialog::getOpenFileName(this); //путь файла сохранённый в типе string
        QFileInfo folderPath=folder_path;//тоже путь к файлу, только сохранённый в другом виде


 qDebug()<<"listfilesindir= "<< listfilesindir(folderPath.path());//не комментировать


//устанавливаем настройки вывода изображения в listWidget
 ui->listWidget_img->setViewMode  (QListWidget::IconMode);
 ui->listWidget_img->setIconSize  (QSize(200,200)       );
 ui->listWidget_img->setResizeMode(QListWidget::Adjust  );

     int i = 0;
     qDebug()<<"size= "<<vtr;
                while (vtr.length() != i)
                {
                             QString file_name(vtr[i].fileName());
                            QString file_path(vtr[i].path());
                            save_file_path=file_path;
                            QString file_full_path=file_path+"/"+file_name;
                             qInfo()<<"filename= "<<file_full_path;
                             //pix_list.load(file_full_path);
                              ui->listWidget_img->addItem(new QListWidgetItem(QIcon(file_full_path),file_name));



                    i++;
                }

   // ui->label->setScaledPixmap(QFileDialog::getOpenFileName(this));


 //загрузка картинки в главное окно
    QPixmap pix;
  //  QDir dir(info.absolutePath);

    pix.load(folder_path);//QFileDialog::getOpenFileName(this) путь к файлу, который выберем. load загружает изображение по этому пути
    ui->label_main->setPixmap(pix);// устанавливаем в label изображение
    ui->label_main->setScaledContents(true); //делаем размер label по размеру изображения
    int pixWidth=pix.width();//ширина изображения
    int labelWidth=ui->label_main->width();//ширина label
    double factor =double(labelWidth)/pixWidth; //сохранение пропорций изображения

    ui->label_main->setFixedWidth(factor * ui->label_main->pixmap()->width());
    ui->label_main->setFixedHeight(factor * ui->label_main->pixmap()->height());//умножаем полную высоту лейбла на коэффицент сохранения сторон
    qDebug()<<"factor= "<< factor;
     save_arg1=factor;

  //  QLabel label_2;
   // QPixmap pixmap("C:/Users/nikit/Desktop/IMG_20210826_110456.jpg");







}

//увеличение и уменьшение


void image::on_button_big_clicked()
{

     save_arg1=save_arg1+0.02;
    ui->label_main->setFixedWidth(save_arg1 * ui->label_main->pixmap()->width());
    ui->label_main->setFixedHeight(save_arg1 * ui->label_main->pixmap()->height());//умножаем полную высоту лейбла на коэффицент сохранения сторон

}

void image::on_button_little_clicked()
{
    save_arg1=save_arg1-0.02;

   ui->label_main->setFixedWidth(save_arg1 * ui->label_main->pixmap()->width());
   ui->label_main->setFixedHeight(save_arg1 * ui->label_main->pixmap()->height());//умножаем полную высоту лейбла на коэффицент сохранения сторон
}



//void image::on_doubleSpinBox1_valueChanged(double arg1)
//{
//    save_arg1=arg1;

//  //  qDebug()<<"arg1= "<< arg1;
//    ui->label->setFixedWidth(arg1 * ui->label->pixmap()->width());
//    ui->label->setFixedHeight(arg1 * ui->label->pixmap()->height());//умножаем полную высоту лейбла на коэффицент сохранения сторон


//}


//поворот направо
void image::on_button_right_clicked()
{
    QPixmap tPixmap(*ui->label_main->pixmap());
    QSize size;
    QRect rc;
    int w, h, x, y;
    x=tPixmap.width();
    y=tPixmap.height();
    size=tPixmap.size();
    rc=ui->label_main->geometry();
    w=rc.width();
    h=rc.height();

    rc.setWidth(h);
    rc.setHeight(w);

    QPixmap rotatePixmap(size*2);

    QPainter p(&rotatePixmap);

    p.translate(rotatePixmap.size().width()/2,   rotatePixmap.size().height()/2);

    p.rotate(90);

    p.translate(-rotatePixmap.size().width()/2, -rotatePixmap.size().height()/2);

    p.drawPixmap(y,x, tPixmap);
    p.end();
    tPixmap=rotatePixmap.copy(0, 2*y-x, y, x);
    ui->label_main->setGeometry(rc);
    ui->label_main->setPixmap(tPixmap);

    ui->label_main->setFixedWidth(save_arg1* ui->label_main->pixmap()->width());
    ui->label_main->setFixedHeight(save_arg1 * ui->label_main->pixmap()->height());


}

//поворот налево
void image::on_button_left_clicked()
{
    QPixmap tPixmap(*ui->label_main->pixmap());
    QSize size;
    QRect rc;
    int w, h, x, y;
    x=tPixmap.width();
    y=tPixmap.height();
    size=tPixmap.size();
    rc=ui->label_main->geometry();
    w=rc.width();
    h=rc.height();

    rc.setWidth(h);
    rc.setHeight(w);

    QPixmap rotatePixmap(size*2);

    QPainter p(&rotatePixmap);

    p.translate(rotatePixmap.size().width()/2,   rotatePixmap.size().height()/2);

    p.rotate(90);

    p.translate(-rotatePixmap.size().width()/2, -rotatePixmap.size().height()/2);

    p.drawPixmap(y,x, tPixmap);
    p.end();
    tPixmap=rotatePixmap.copy(0, 2*y-x, y, x);
    ui->label_main->setGeometry(rc);
    ui->label_main->setPixmap(tPixmap);

    // выставление пропорций изображения, чтобы оно не было вытянутым
    ui->label_main->setFixedWidth( save_arg1* ui->label_main->pixmap()->width());
    ui->label_main->setFixedHeight(save_arg1 * ui->label_main->pixmap()->height());

}







//получение названия картинки из listWidget и установка этой картинки на главное место
void image::on_listWidget_img_currentTextChanged(const QString &currentText)
{
  //  qDebug()<<"currentText= "<<currentText;

    QString file_full_path=save_file_path+"/"+currentText;

    QPixmap pix;
  //  QDir dir(info.absolutePath);

    pix.load(file_full_path);//QFileDialog::getOpenFileName(this) путь к файлу, который выберем. load загружает изображение по этому пути
    ui->label_main->setPixmap(pix);// устанавливаем в label изображение
    ui->label_main->setScaledContents(true); //делаем размер label по размеру изображения
    int pixWidth=pix.width();//ширина изображения
    int labelWidth=ui->label_main->width();//ширина label
    double factor =double(labelWidth)/pixWidth; //сохранение пропорций изображения

    ui->label_main->setFixedWidth(factor * ui->label_main->pixmap()->width());
    ui->label_main->setFixedHeight(factor * ui->label_main->pixmap()->height());//умножаем полную высоту лейбла на коэффицент сохранения сторон
    qDebug()<<"factor= "<< factor;
     save_arg1=factor;


}
