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
#include <QTime>

/*
    Constructor class History
    @param QString filename, QWidget *parent
    @return -
*/
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

/*
    Set text in tableWidget in history window (takes information from the file)

    @param QString filename
    @return -
*/
void History::set_text(QString filename)
{
    QFile f1(filename);
    if (!f1.open(QFile::ReadOnly)) return;
    QByteArray input;

    for (int i=0;i<5;i++)
    {
        input=f1.readLine();
        if (input.isEmpty())continue;
        //delete the character to the next line
        input.remove(input.length()-2,2);
        ui->tableWidget->item(i,0)->setText(input.left(10));//for name
        ui->tableWidget->item(i,1)->setText(input.left(18).right(8));//for time
        ui->tableWidget->item(i,2)->setText(input.right(input.size()-18));// for count of moves
    }

    f1.close();
}

/*
    swap all elemets of rows

    @param int r1, int r2 - row indices
    @return -
*/
void History::swap_raw(int r1, int r2)
{
    //three coloms: 0-name; 1-time; 2-count of moves
    for (int i=0;i<3;i++)
    {
        QString txt=ui->tableWidget->item(r1, i)->text();
        ui->tableWidget->item(r1, i)->setText(ui->tableWidget->item(r2, i)->text());
        ui->tableWidget->item(r2, i)->setText(txt);
    }


}

/*
    sorting records by time

    @param -
    @return -
*/
void History::on_sort_by_time_radiobtn_clicked()
{
    for(int i=0;i<5;i++)
        for (int j=0;j<4;j++)
        {
            if (QTime::fromString( ui->tableWidget->item(j, 1)->text())>
                QTime::fromString( ui->tableWidget->item(j+1, 1)->text())
                ||ui->tableWidget->item(j, 1)->text().isEmpty())
            {
                swap_raw(j,j+1);
            }
        }
}

/*
    sorting records by count steps

    @param -
    @return -
*/
void History::on_sort_by_step_radiobtn_clicked()
{
    for(int i=0;i<5;i++)
        for (int j=0;j<4;j++)
        {
            if (ui->tableWidget->item(j, 2)->text().toInt() >
                    ui->tableWidget->item(j+1, 2)->text().toInt()
                    ||ui->tableWidget->item(j, 1)->text().isEmpty())
            {
                swap_raw(j,j+1);
            }
        }
}
