/*
    K-28
    mainwindow.cpp
    Purpose: implementation of class MainWindow functions
    (initial game window)
    @author Mariia Kushnirenko
    @version 08/1218
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "form.h"
#include "ui_form.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Exit", "Do you really want to leave the game?",
                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        close();
    }
}

void MainWindow::on_pushButton_start_clicked()
{
    Form *f = new Form(ui->HardMode->checkState());
    f->setFocus();
    f->show();
    this->close();
}


void MainWindow::on_pushButton_history_clicked()
{
   History *h=new History("Filename.txt");
   h->show();
}
