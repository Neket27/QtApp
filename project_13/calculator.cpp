#include "calculator.h"
#include "ui_calculator.h"

double num_first;

calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calculator)
{

    ui->setupUi(this);
    // соединение с digits_numbers()
    connect(ui->button_0,SIGNAL(clicked()),this,SLOT(digits_numbers()));//вызываем функцию digits_numbers() при нажатии на кнопку нуль
    connect(ui->button_1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->button_2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->button_3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->button_4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->button_5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->button_6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->button_7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->button_8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->button_9,SIGNAL(clicked()),this,SLOT(digits_numbers()));

    connect(ui->button_plus,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->button_minus,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->button_multiply,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->button_division,SIGNAL(clicked()),this,SLOT(operations()));

    ui->button_plus->setCheckable(true);
    ui->button_minus->setCheckable(true);
    ui->button_multiply->setCheckable(true);
    ui->button_division->setCheckable(true);

}

calculator::~calculator()
{
    delete ui;
}



void calculator:: digits_numbers()
{
    //sender() возращает кнопку, которая была нажата
    QPushButton *my_button =(QPushButton *)sender();

    double all_numbers;
    //обращаемся к переменной resulte с помощью text() считываем поле resulte и добавляем, что написано в текстовом поле кнопки.
    all_numbers=(ui->resulte->text()+my_button->text()).toDouble();
    //перевод типа double в string
    QString string_result;
    string_result= QString::number(all_numbers);

    ui->resulte->setText(string_result);

}

//точка
void calculator::on_button_C_2_clicked()
{
    //contains проверяет есть ли символ в строке
    if((ui-> resulte->text().contains("."))==false)
         ui->resulte->setText(ui->resulte->text()+".");

}

void calculator:: operations()
{
    //sender() возращает кнопку, которая была нажата
    QPushButton *my_button =(QPushButton *)sender();
    num_first =ui->resulte ->text().toDouble();
    ui->label_move->setText(QString::number(num_first));
    ui->resulte->setText("");
    my_button->setChecked(true);
}



//равно
void calculator::on_button_equals_clicked()
{
    double labelNumber, num_second;
    QString string_result;
    num_second=ui->resulte->text().toDouble();


    if(ui->button_plus->isChecked()){
        labelNumber=num_first+num_second;
        string_result= QString::number(labelNumber);
        ui->resulte->setText(string_result);
        //если уже нажали на кнопку, то больше не сработает
        ui->button_plus->setChecked(false);
    }
    else if (ui->button_minus->isChecked()){
        labelNumber=num_first-num_second;
        string_result= QString::number(labelNumber);
        ui->resulte->setText(string_result);
        //если уже нажали на кнопку, то больше не сработает
        ui->button_minus->setChecked(false);
    }
    else if (ui->button_multiply->isChecked()){
        labelNumber=num_first*num_second;
        string_result= QString::number(labelNumber);
        ui->resulte->setText(string_result);
        //если уже нажали на кнопку, то больше не сработает
        ui->button_multiply->setChecked(false);
    }
    else if(ui->button_division-> isChecked()){
        if(num_second==0){
            ui->resulte->setText("(0_0)");
        }
        else
        {
        labelNumber=num_first / num_second;
        string_result= QString::number(labelNumber);
        ui->resulte->setText(string_result);
        //если уже нажали на кнопку, то больше не сработает
        ui->button_division->setChecked(false);
        }
    }
}
//очистка результата
void calculator::on_button_clear_clicked()
{
    num_first=0;
    ui->resulte->setText("0");
    ui->label_move->setText("");


}

