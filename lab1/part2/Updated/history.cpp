/*
    K-28
    Game.cpp
    Purpose: implementation of class History functions
    (class for visualization save history)
    @author Mariia Kushnirenko
    @version 22/04/19
*/


#include "history.h"
#include "ui_history.h"
#include <QFile>
#include <QTableWidgetItem>
#include <QDebug>
#include <QTime>

const QString wayTo="filename.txt";

History::History(QString filename, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);

    this->setLayout(ui->Main_VLayout);

    set_text(filename);
    on_sort_by_step_radiobtn_clicked();
    this->setFixedSize(this->size());
}

History::~History()
{
    delete ui;
}

void History::set_text(QString filename)
{
    QFile f1(filename);
    if (!f1.open(QFile::ReadOnly)) return;
    QByteArray input;

    for (int i=0;i<5;i++)
    {
        input=f1.readLine();
        if (input.isEmpty())continue;
        input.remove(input.length()-2,2);
        ui->tableWidget->item(i,0)->setText(input.left(10));
        ui->tableWidget->item(i,1)->setText(input.left(18).right(8));
        ui->tableWidget->item(i,2)->setText(input.right(input.size()-18));
    }

    f1.close();
}

void History::swap_raw(int r1, int r2)
{
    for (int i=0;i<3;i++)
    {//swap(ui->tableWidget->item(r1, i), ui->tableWidget->item(r2, i))
        QString txt=ui->tableWidget->item(r1, i)->text();
        ui->tableWidget->item(r1, i)->setText(ui->tableWidget->item(r2, i)->text());
        ui->tableWidget->item(r2, i)->setText(txt);
    }


}

void History::on_sort_by_time_radiobtn_clicked()
{
    for(int i=0;i<5;i++)
        for (int j=0;j<4;j++)
        {
            if (QTime::fromString( ui->tableWidget->item(j, 1)->text())>QTime::fromString( ui->tableWidget->item(j+1, 1)->text())||ui->tableWidget->item(j, 1)->text().isEmpty())
            {
                swap_raw(j,j+1);
            }
        }
}

void History::on_sort_by_step_radiobtn_clicked()
{
    for(int i=0;i<5;i++)
        for (int j=0;j<4;j++)
        {
            if (ui->tableWidget->item(j, 2)->text().toInt() > ui->tableWidget->item(j+1, 2)->text().toInt()||ui->tableWidget->item(j, 1)->text().isEmpty())
            {
                swap_raw(j,j+1);
            }
        }
}
