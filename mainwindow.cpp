#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

double numberFirst;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_plus_minus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(math_operations()));

    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_sqrt->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton* )sender();
    QString resultString;
    double all_numbers;

    if (ui->result_show->text().contains(".")&&button->text() == "0")
    {
        resultString = ui->result_show->text()+button->text();
    }
    else
    {
        all_numbers = (ui->result_show->text() + button->text()).toDouble();
        resultString = QString::number(all_numbers, 'g', 15);
    }

    ui->result_show->setText(resultString);
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton* )sender();
    QString resultString;
    double all_numbers;

    if(button->text() == "+/-")
    {
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers *= -1;
        resultString = QString::number(all_numbers, 'g', 15);
        ui->result_show->setText(resultString);
    }
    else if(button->text() == "%")
    {
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers *= (numberFirst / 100);
        resultString = QString::number(all_numbers, 'g', 15);
        ui->result_show->setText(resultString);
    }
}

void MainWindow::math_operations()
{
    QPushButton *button = (QPushButton* )sender();

    numberFirst = ui->result_show->text().toDouble();
    ui->result_show->setText("");
    button->setChecked(true);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->result_show->text().contains('.')))
    {
        ui->result_show->setText(ui->result_show->text() + '.');
    }
}

void MainWindow::on_pushButton_AC_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_sqrt->setChecked(false);

    ui->result_show->setText("0");
}

void MainWindow::on_pushButton_equal_clicked()
{
    double labelNumber, numberSecond;
    QString resultString;

    numberSecond = ui->result_show->text().toDouble();

    if(ui->pushButton_plus->isChecked())
    {
        labelNumber = numberFirst + numberSecond;
        resultString = QString::number(labelNumber, 'g', 15);
        ui->result_show->setText(resultString);
        ui->pushButton_plus->setChecked(false);
    }
    else if(ui->pushButton_minus->isChecked())
    {
        labelNumber = numberFirst - numberSecond;
        resultString = QString::number(labelNumber, 'g', 15);
        ui->result_show->setText(resultString);
        ui->pushButton_minus->setChecked(false);
    }
    else if(ui->pushButton_multiply->isChecked())
    {
        labelNumber = numberFirst * numberSecond;
        resultString = QString::number(labelNumber, 'g', 15);
        ui->result_show->setText(resultString);
        ui->pushButton_multiply->setChecked(false);
    }
    else if(ui->pushButton_divide->isChecked())
    {
        labelNumber = numberFirst / numberSecond;
        if(numberSecond == 0)
        {
            ui->result_show->setText("0");
        }
        else
        {
            resultString = QString::number(labelNumber, 'g', 15);
            ui->result_show->setText(resultString);
            ui->pushButton_divide->setChecked(false);
        }
    }
    else if(ui->pushButton_sqrt->isChecked())
    {
       labelNumber = qSqrt(numberFirst);
       if (numberFirst < 0)
       {
           ui->result_show->setText("Uncorrect input");
       }
       else
       {
           resultString = QString::number(labelNumber, 'g', 15);
           ui->result_show->setText(resultString);
           ui->pushButton_sqrt->setChecked(false);
       }
    }
}
