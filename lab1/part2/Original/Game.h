#ifndef GAME_H
#define GAME_H

/*
    K-28
    Game.h
    Purpose: idescription of class Game functions
    (logic (brain) game)
    @author Mariia Kushnirenko
    @version 08/12/18
*/


#include <QList>
#include <QWidget>
#include <QDebug>
class QGridLayout;
class QPoint;
class QPushButton;

class Game : public QWidget
{
    Q_OBJECT
public:
    Game(QString s, QWidget* parent = nullptr);
    void createButton(QPushButton*, int, int, int);
    void ChangePhoto(QString s);
    QString FileDir;
    int countMoves=0;

signals:
    void Smove();

private:
    QList<QPushButton*> buttons;
    QList<int> numbers;
    QGridLayout* grid;
    QPoint path;//empty cell
    QPixmap *px[15];//for showing images on screen
    void checkGameOver();

public slots:
    void move();
};

#endif
