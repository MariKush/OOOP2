#include "history.h"
#include "ui_history.h"
#include <QFile>

const QString wayTo="filename.txt";

History::History(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);

    QFile f1(wayTo);
    char *input_line=new char[30];
    f1.readLine(input_line, 30);
}

History::~History()
{
    delete ui;
}
