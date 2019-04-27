#ifndef GAME_H
#define GAME_H

/*
    K-28
    Game.h
    Purpose: idescription of class Game functions
    (logic (brain) game)
    @author Mariia Kushnirenko
    @version 22/04/19
*/


#include <QList>
#include <QWidget>
#include <QDebug>
#include "history.h"

#include <gtest/gtest.h>
class QGridLayout;
class QPoint;
class QPushButton;

class Game : public QWidget
{
    Q_OBJECT
public:
    Game(QString s, int width, QWidget* parent = nullptr);
    void createButton(QPushButton*, int, int, int);
    void changePhoto(QString s);
    void rewriteScoreFile(QString filename);

    void clickButton(int button_key);
    QString FileDir;
    int countMoves=0;

signals:
    void Smove();
    void click();

private:
    int width;
    QList<QPushButton*> buttons;
    QList<int> numbers;
    QGridLayout* grid;
    QPoint path;//empty cell
    QPixmap **px;//for showing images on screen

    void checkGameOver();
    QString getFilename();

    //this tests is friend for this class
    FRIEND_TEST(Form,CanBeSolve);
    FRIEND_TEST(Form,MoveCells);
    FRIEND_TEST(Form,ChangePhoto);
    FRIEND_TEST(Form,KeyClickEvent);
public slots:
    void move();
};

#endif
