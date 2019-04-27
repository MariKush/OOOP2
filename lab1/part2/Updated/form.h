#ifndef FORM_H
#define FORM_H

/*
    K-28
    form.h
    Purpose: idescription of class Form functions
    (for box with a gaming field)
    @author Mariia Kushnirenko
    @version 22/04/19
*/


#include <QWidget>
#include "Game.h"
#include <QElapsedTimer>
#include <QTimer>
class QHBoxLayout;
class QVBoxLayout;

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(bool HardMode=true, int width=4, QWidget *parent = nullptr);//nonconverting constructor
    QTime getTime();
    QString getHard();
    void winGame();
    ~Form();

private slots:
    void on_NewGame_clicked();
    void on_ExitGame_clicked();
    void on_CnangePhoto_clicked();
    void updateCountOfMoves();
    void setTime();

private:
    Ui::Form *ui;
    Game* game;
    bool hardMode;
    int width;
    QHBoxLayout* settingsLayout;
    QHBoxLayout* photoLayout;
    QVBoxLayout* layout;
    QHBoxLayout* counter;
    QTimer* timer;
    QElapsedTimer time;
    QString wayTo;

    void keyPressEvent(QKeyEvent *e);
    bool eventFilter(QObject *obj,QEvent *event);
    void changePhoto(QString filename);

    //this tests is friend for this class
    FRIEND_TEST(Form,SettertGetters);
    FRIEND_TEST(Form,CanBeSolve);
    FRIEND_TEST(Form,MoveCells);
    FRIEND_TEST(Form,ChangePhoto);
    FRIEND_TEST(Form,KeyClickEvent);
};

#endif // FORM_H
