#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

 /** CONSTANTS **/
 /**
 * Prefix | Meaning
 * UOP  = Unary Operation
 * N    = Number
 */
const QString UOP_MORE_MINUS = "+/-";
const QString UOP_PORCENT = "%";
const short N_ZERO = 0;
const short N_NEGATIVE_ONE = -1;
const double N_PORCENT_ONE = 0.01;
/** END CONSTANTS **/

/** GLOBAL VARIABLES **/
double firstNum;
double secondNum;
bool typingNewNumber = false;
bool typingSecondNumber = false;
/** END GLOBAL VARIABLES **/


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Number buttons  */
    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));

    /* Unary operators buttons */
    connect(ui->pushButton_moreMinus, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_porcent, SIGNAL(released()), this, SLOT(unary_operation_pressed()));

    /* Operators buttons */
    connect(ui->pushButton_add, SIGNAL(released()), this, SLOT(simple_operation_pressed()));
    connect(ui->pushButton_subtract, SIGNAL(released()), this, SLOT(simple_operation_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(simple_operation_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(simple_operation_pressed()));

    /* Set buttons */
    ui->pushButton_add->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Add the pressed number in the result label
 */
void MainWindow::digit_pressed()
{
    // Sender return a pointer of the object signal
    QPushButton * button = (QPushButton *) sender();

    QString newNumberLabel;
    double labelNumber;

    if((ui->pushButton_add->isChecked() || ui->pushButton_subtract->isChecked()
             || ui->pushButton_multiply->isChecked() || ui->pushButton_divide->isChecked()) && !typingSecondNumber)
    {
        // "Clean" the label and add only the new pressed number
        labelNumber = button->text().toDouble();
        // Convert the number in string
        newNumberLabel = QString::number(labelNumber, 'g', 15);

        typingNewNumber = false;
        typingSecondNumber = true;
        qDebug() << "ENTROU 1";
    }
    else if(typingNewNumber)    // Case after pressed equals button
    {
        // "Clean" the label and add only the new pressed number
        labelNumber = button->text().toDouble();
        // Convert the number in string
        newNumberLabel = QString::number(labelNumber, 'g', 15);
        typingNewNumber = false;
        qDebug() << "ENTROU 2";
    }
    else
    {
        if(ui->label_result->text().contains(".") && button->text() == QString::number(N_ZERO)){
            newNumberLabel = ui->label_result->text() + button->text();
            qDebug() << "ENTROU 3";
        }
        else
        {
            // The number in display + new pressed number
            labelNumber = (ui->label_result->text() + button->text()).toDouble();
            // Convert the number in string
            newNumberLabel = QString::number(labelNumber, 'g', 15);
            qDebug() << "ENTROU 4";
        }
        typingNewNumber = false;
    }

    // Print label results
    ui->label_result->setText(newNumberLabel);

}

/**
 * @brief Add a point in the result label case not exists
 */
void MainWindow::on_pushButton_point_released()
{
    typingNewNumber = false;

    if(ui->label_result->text().contains("."))
    {
        return;
    }
    else{
        ui->label_result->setText(ui->label_result->text() + ".");
    }
}

/**
 * @brief Apply operation '+/-' or '%'. Unary operation is a operation with only one operator.
 */
void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton *) sender();
    QString operation = button->text();

    double labelNumber = ui->label_result->text().toDouble();

    if(operation == UOP_MORE_MINUS){
        labelNumber = labelNumber * (double)N_NEGATIVE_ONE;
    }else if(operation == UOP_PORCENT){
        labelNumber = labelNumber * (double)N_PORCENT_ONE;
    }

    typingNewNumber = true;

    QString newNumbemLabel = QString::number(labelNumber, 'g', 15);
    ui->label_result->setText(newNumbemLabel);
}

/**
 * @brief Clear the value in result label
 */
void MainWindow::on_pushButton_clear_released()
{
    // Basically, resets all variables
    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    typingNewNumber = true;
    typingSecondNumber = false;

    ui->label_result->setText(QString::number(N_ZERO));
}

/**
 * @brief Calculate and show the result of operation
 */
void MainWindow::on_pushButton_equals_released()
{
    double labelNumber;

    secondNum = ui->label_result->text().toDouble();

    if(ui->pushButton_add->isChecked())
    {
        labelNumber = firstNum + secondNum;
        ui->pushButton_add->setChecked(false);
    }
    else if(ui->pushButton_subtract->isChecked())
    {
        labelNumber = firstNum - secondNum;
        ui->pushButton_subtract->setChecked(false);
    }
    else if(ui->pushButton_multiply->isChecked())
    {
        labelNumber = firstNum * secondNum;
        ui->pushButton_multiply->setChecked(false);
    }
    else if(ui->pushButton_divide->isChecked())
    {
        labelNumber = firstNum / secondNum;
        ui->pushButton_divide->setChecked(false);
    }
    else
    {
        //labelNumber = ui->label_result->text().toDouble();
        return;
    }

    QString resultLabelNum = QString::number(labelNumber, 'g', 15);
    ui->label_result->setText(resultLabelNum);

    typingNewNumber = true;
    typingSecondNumber = false;
}

/**
 * @brief Saves which operation button was pressed and the first number insered
 */
void MainWindow::simple_operation_pressed()
{
    QPushButton * button = (QPushButton *)sender();

    button->setChecked(true);

    // Save in global variable the first number of the operation
    firstNum = ui->label_result->text().toDouble();
}



