#ifndef IMAGE_H
#define IMAGE_H
#include <QFileInfo>
#include <QDialog>
#include <QVector>
namespace Ui {
class image;
}

class image : public QDialog
{
    Q_OBJECT

public:
    explicit image(QWidget *parent = nullptr);
    ~image();

    double save_arg1=0.1;


private slots:
    void on_button_load_clicked();

    void on_button_left_clicked();

    void on_button_right_clicked();

   // void on_doubleSpinBox1_valueChanged(double arg1);

    QVector<QFileInfo> listfilesindir(QString path);

   // QString listfilesindir(QString path);

    void on_button_big_clicked();

    void on_button_little_clicked();



    void on_listWidget_img_currentTextChanged(const QString &currentText);


private:
    Ui::image *ui;

     QString save_file_path;

public:
    QVector <QFileInfo> vtr;




};

#endif // IMAGE_H
