#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXlsx>
#include <string>
#include <map>
#include "Parser.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int find_empty_row(const QXlsx::Document &xlsx)
{
    int         row = 1;
    QXlsx::Cell *cell = xlsx.cellAt(row, 1);

    while (cell)
    {
        row++;
        cell = xlsx.cellAt(row, 1);
    }
    return (row);
}

void Pars(QString &str, QXlsx::Document &xlsx)
{
    int row = find_empty_row(xlsx);

    Parser data(str);

    xlsx.write(row, 1, data.getSeries());
    xlsx.write(row, 2, data.getNumber());
    xlsx.write(row, 3, data.getFullName());
    xlsx.write(row, 4, data.getIssued());
    xlsx.write(row, 5, data.getBithday());
    xlsx.write(row, 6, data.getPassportDate());
    xlsx.write(row, 7, data.getRemainder());
}

void MainWindow::on_pushButton_clicked()
{
    str = ui->textEdit->toPlainText();
    ui->textEdit->clear();
    QXlsx::Document xlsx("/Users/deniskozarezov/Desktop/test1.xlsx");

    Pars(str, xlsx);

    xlsx.save();
}

