#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

/** CONSTANTS **/
const QString OP_MORE_MINUS = "+/-";
const QString OP_PORCENT = "%";
const short N_NEGATIVE_ONE = -1;
const double N_PORCENT_ONE = 0.01;


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
    connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_subtract, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_equals, SIGNAL(released()), this, SLOT(digit_pressed()));

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

    // The number in display + new pressed number
    double labelNumber = (ui->label_result->text() + button->text()).toDouble();

    // Convert the number in string
    QString newNumberLabel = QString::number(labelNumber, 'g', 15);

    // Print label results
    ui->label_result->setText(newNumberLabel);

}

/**
 * @brief Add a point in the result label
 */
void MainWindow::on_pushButton_point_released()
{
    ui->label_result->setText(ui->label_result->text() + ".");
}

/**
 * @brief Apply operation '+/-' or '%'. Unary operation is a operation with only one operator.
 */
void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton *) sender();
    QString operation = button->text();

    double labelNumber = ui->label_result->text().toDouble();

    if(operation == OP_MORE_MINUS){
        labelNumber = labelNumber * (double)N_NEGATIVE_ONE;
    }else if(operation == OP_PORCENT){
        labelNumber = labelNumber * (double)N_PORCENT_ONE;
    }

    QString newNumbemLabel = QString::number(labelNumber, 'g', 15);
    ui->label_result->setText(newNumbemLabel);
}

/**
 * @brief
 */
void MainWindow::single_operation_pressed()
{

}
