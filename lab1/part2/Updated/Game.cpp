/*
    K-28
    Game.cpp
    Purpose: implementation of class Game functions
    (logic (brain) game)
    @author Mariia Kushnirenko
    @version 08/1218
*/

#include "Game.h"
#include "form.h"
#include "mainwindow.h"
#include <QGridLayout>
#include <QPoint>
#include <QPushButton>
#include <QTime>
#include "QMessageBox"
#include <QDir>
#include <QFile>
#include <QInputDialog>

/*
    Constructor class Game
    @param QString s
           QWidget
    @return -
*/
Game::Game(QString s, QWidget* parent)
{
    this->setParent(parent);
    grid = new QGridLayout(this);
    grid->setHorizontalSpacing(1);
    grid->setVerticalSpacing(1);

    QTime midnight(0, 0, 0);
    srand(midnight.msecsTo(QTime::currentTime()));
    FileDir=QDir::currentPath();
    FileDir=FileDir.left(FileDir.lastIndexOf(QChar('/')))+"/pictures/";

    // pictures
    ChangePhoto(s);

    int n;
    do
    {
        numbers.clear();
        //random field filling
        for(int i = 0; i < 15; i++)
        {
            do
                n = rand() % 15 + 1;
            while(numbers.contains(n));
            numbers << n;
        }
        n = 0;

        //check (is possibly make it?)
        for(int i = 2; i <= 15; i++)
            for(int j = 0; j < numbers.indexOf(i); j++)
            {
                if(numbers[j] < i)
                {
                    ++n;
                }
            }
    } while(n%2 == 1);

    //work with coordinates

    //set empty cell
    do
        path.setY(rand() % 4);
    while(0 != path.y()%2);

    path.setX(rand() % 4);


    n = 0;

    //creale all buttons
    for(int y = 0; y < 4; ++y) // line
        for(int x = 0; x < 4; ++x) // column
        {
            //current cell must be empty
            if(path.x() == x && path.y() == y)
                continue;

            createButton(nullptr, numbers[n++], x, y);
        }
    setLayout(grid);
}


/*
    For move cells
    @param QPushButton* b, int nom,
           int x, int y - coordinats
    @return -
*/
void Game::createButton(QPushButton* b, int nom, int x, int y) // Create a button
{
    QPushButton* btn = b;
    if(!btn)
    {
        btn = new QPushButton();
        buttons << btn;
        connect(btn, SIGNAL(clicked()), this, SLOT(move()));
        btn->setFixedSize(150,150);

        QIcon ButtonIcon(*px[nom-1]);
        btn->setIcon(ButtonIcon);
        btn->setIconSize(QSize(150,150));

    }
    grid->addWidget(btn, y, x);
}


void Game::click_button(int button_key)
{
    qDebug()<<path;
    QPoint new_path(path);

    switch (button_key) {
    case Qt::Key_Up: {
        new_path.setY(new_path.y()+1);
        if(new_path.y()==width)return;
        break;
    }
    case Qt::Key_Down: {
        new_path.setY(new_path.y()-1);
        if(new_path.y()==-1)return;
        break;
    }
    case Qt::Key_Left: {
        new_path.setX(new_path.x()+1);
        if (new_path.x()==width)return;
        break;
    }
    case Qt::Key_Right:{
        new_path.setX(new_path.x()-1);
        if (new_path.x()==-1)return;
        break;
    }
    default: qDebug()<<"bag"; exit(1488);
    }
    qDebug()<<new_path;
    static_cast<QPushButton*>(grid->itemAtPosition(new_path.y(), new_path.x())->widget())->click();
}

/*
    For move cells
    @param -
    @return -
*/
void Game::move()
{
    emit click();
    int x, y, rs, cs;
    QPushButton* clickedBtn = static_cast<QPushButton*>(sender());
    grid->getItemPosition(grid->indexOf(clickedBtn), &y, &x, &rs, &cs);
    if((path.x() == x && (path.y() == y+1 || path.y() == y-1))
    || (path.y() == y && (path.x() == x+1 || path.x() == x-1))) // Can you move the button?
    {
        countMoves++;
        emit Smove();

        // we remove the button from the old place
        grid->removeWidget(clickedBtn);

        // and add it to a free cell
        createButton(clickedBtn, 0, path.x(), path.y());

        // and we update the coordinates of a free cell
        path = QPoint(x, y);

        // Checking for the end of the game
        checkGameOver();
    }
}

/*
    Сheck for: "is game over?"
    @param -
    @return -
*/
void Game::checkGameOver()
{
    int i=1, n=0;

    for(int y = 0; y > grid->rowCount(); ++y) // line
    {
        for(int x = 0; x < grid->columnCount(); ++x) // column
        {
            if(grid->itemAtPosition(y, x) == nullptr)
                continue;
            n = numbers.indexOf(i++);
            if(buttons[n] != (QPushButton*)grid->itemAtPosition(y, x)->widget())
                return;
        }
    }

    // check whether the last cell is free
    if(path.y() == grid->rowCount()-1 && path.x() == grid->columnCount()-1)
    {
        // the game is over
        // block all buttons
        for(QList<QPushButton*>::const_iterator it = buttons.begin(); it != buttons.end(); ++it)
            (*it)->setDisabled(true);

        static_cast<Form*>(parent())->vin_game();

        QMessageBox::information(this, "message", "THE VICTORY!!!");

        QString filename=get_filename();
        rewrite_score_file(filename);

        History *h=new History(filename);
        h->show();


    }
}

QString Game::get_filename()
{
    QString filename="filename";
    filename+=static_cast<Form*>(parent())->getHard();
    filename+=QString::number(width);
    return filename+".txt";
}

/*
    Change 15 photos for eltment class QPixmap

    @param QString - fileName
    @return -
*/
void Game::ChangePhoto(QString s)
{
    for(int i=0;i<15;i++)
    {
        px[i]=new QPixmap(s+QString::number(i+1)+".jpg");
    }
}

void Game::rewrite_score_file(QString filename)
{
    int deleted_row=-1;
    int min_count=countMoves;
    QFile f1(filename);
    bool b=false;
    if (!f1.open(QFile::ReadWrite))//file dont exist
    {
        b=true;
    }
    else
    {
        QByteArray arr;
        for (int var = 0; var < 5; var++) {
            arr=f1.readLine();
            qDebug()<<arr;
            if (arr.isEmpty())
            {
                deleted_row=-1;
                b=true;
                var=5;
                continue;
            }
            int count_moves;

            count_moves=arr.right(arr.length()-10-8).left(arr.length()-10-8-2).toInt();
            qDebug()<<count_moves;
            if (min_count<count_moves)
            {
                min_count=count_moves;
                deleted_row=var;
                b=true;
            }
            arr.clear();
        }

    }
    f1.close();

    bool ok;
    QString text;
    if (b)
    {
        do{

            text= QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                     tr("User name:"),QLineEdit::Normal,
                                                     QDir::home().dirName(), &ok);
        }while(!ok||text.isEmpty());
        text=text.left(10);
        while (text.size()<10)text+=" ";
        f1.open(QFile::ReadWrite);


        if (deleted_row==-1)
        {
            while (f1.getChar(char())) {}
            QByteArray put=text.toLatin1();
            put+=static_cast<Form*>(parent())->getTime().toString();
            qDebug()<<static_cast<Form*>(parent())->getTime();
            put+=QString::number(countMoves).toLatin1();
            put+="\r\n";
            qDebug()<<put;
            f1.write(put);
        }
        else
        {

            QString tmp="tmp.tmp";
            QFile f2(tmp);
            f2.open(QFile::WriteOnly);
            for(int i=0;i<5;i++)
            {
                 QByteArray put=f1.readLine();
                 if (i==deleted_row)
                 {
                     put=text.toLatin1();
                     put+=static_cast<Form*>(parent())->getTime().toString();
                     put+=QString::number(countMoves).toLatin1();
                     put+="\r\n";
                     qDebug()<<put;
                     f2.write(put);
                 }
                 else {
                     f2.write(put);
                 }
            }

            f1.close();
            QFile::remove(filename);
            f2.rename(filename);
            f2.close();
        }
    }
}





