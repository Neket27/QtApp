#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class calculator; }
QT_END_NAMESPACE

class calculator : public QMainWindow
{
    Q_OBJECT

public:
    calculator(QWidget *parent = nullptr);
    ~calculator();



private:
    Ui::calculator *ui;

private slots:
    void digits_numbers();

    void on_button_C_2_clicked();
    void operations();
    void on_button_equals_clicked();
    void on_button_clear_clicked();
};
#endif // CALCULATOR_H
