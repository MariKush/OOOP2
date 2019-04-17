#include "history.h"
#include "ui_history.h"
#include <QFile>
#include <QTableWidgetItem>
#include <QDebug>

const QString wayTo="filename.txt";

History::History(QString filename, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);

    this->setLayout(ui->Main_VLayout);

    set_text(filename);

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
