/*
    K-28
    form.cpp
    Purpose: implementation of class Form functions
    (for box with a gaming field)
    @author Mariia Kushnirenko
    @version 22/04/19
*/

#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTime>


/*
    Designer class Form

    @param bool HardMode - for set hard mode
    @return -
*/
Form::Form(bool HardMode, int width, QWidget *parent):
    QWidget(parent),
    ui(new Ui::Form),
    game(nullptr)
{
    ui->setupUi(this);

    this->hardMode=HardMode;
    this->width=width;

    layout = new QVBoxLayout(this);
    settingsLayout = new QHBoxLayout;
    photoLayout = new QHBoxLayout;

    //add settings buttoms in Layout
    settingsLayout->addWidget(ui->NewGame);
    settingsLayout->addWidget(ui->CnangePhoto);
    settingsLayout->addWidget(ui->ExitGame);

    layout->addLayout(settingsLayout);

    timer=new QTimer;
    timer->start(100);

    //set the default image
    QDir dir=QDir::current();
    dir.cdUp();
    dir.cd("pictures");
    while (!dir.cd("autumn"+QString::number(width)))
    {
        dir.mkdir("autumn"+QString::number(width));
    }
    wayTo=dir.absolutePath()+"/";
    changePhoto(wayTo.left(wayTo.left(wayTo.length()-1).lastIndexOf('/')+1)+"autumn.png");

    //fixing the size of the field
    this->setFixedSize(this->size());

    setLayout(layout);
}


Form::~Form()
{
    delete ui;
}


/*
    Updating the number of moves and start time count after first move

    @param -
    @return -
*/
void Form::updateCountOfMoves()
{
    ui->countMoves->setText(QString::number(game->countMoves)+" moves");
    if (game->countMoves==1)time.start();
}

/*
    For regular updates of the time spent

    @param -
    @return -
*/
void Form::setTime()
{
    if (!time.isValid()) return;
    QTime t(0,0);
    t=t.addMSecs(static_cast<int>(time.elapsed()));
    ui->countTime->setText("Time: "+t.toString());
}

/*
    To get game time

    @param -
    @return QTime (time of making a puzzle)
*/
QTime Form::getTime()
{
    QTime t(0,0);
    if (!time.isValid()) return t;
    t=t.addMSecs(static_cast<int>(time.elapsed()));
    return t;
}

/*
    To get level game

    @param -
    @return QString (game level)
*/
QString Form::getHard()
{
    if (hardMode)return "hard";
    else return "nohard";
}

/*
    to handle the keystroke event

    @param QObject and QEvent
    @return bool
*/
bool Form::eventFilter(QObject *obj,QEvent *event)
{
    QKeyEvent *keyEvent = nullptr;//event data, if this is a keystroke event
    bool result = false;//return true to consume the keystroke

    if (event->type() == QEvent::KeyPress)
    {
         keyEvent = dynamic_cast<QKeyEvent*>(event);
         this->keyPressEvent(keyEvent);
         result = true;
    }//if type()

    else if (event->type() == QEvent::KeyRelease)
    {
        keyEvent = dynamic_cast<QKeyEvent*>(event);
        this->keyReleaseEvent(keyEvent);
        result = true;
    }//else if type()

    //### Standard event processing ###
    else
        result = QObject::eventFilter(obj, event);

    return result;
}

/*
    for press on buttons (сalling the method for the game)

    @param QKeyEvent *e
    @return -
*/
void Form::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Left)game->clickButton(Qt::Key_Left);
    if(e->key()==Qt::Key_Right)game->clickButton(Qt::Key_Right);
    if(e->key()==Qt::Key_Up)game->clickButton(Qt::Key_Up);
    if(e->key()==Qt::Key_Down)game->clickButton(Qt::Key_Down);
}

/*
    timer recall, at the end of the game

    @param -
    @return -
*/
void Form::winGame()
{
    disconnect(this->timer, SIGNAL(timeout()), this, SLOT(setTime()));
}

/*
    Create new game

    @param -
    @return -
*/
void Form::on_NewGame_clicked()
{
    //delete the old field
    if(game)
    {
        time.invalidate();
        photoLayout->removeWidget(game);
        if (!hardMode)
            photoLayout->removeWidget(ui->originalPhoto);
        layout->removeItem(counter);
        layout->removeItem(photoLayout);

        delete game;
    }

    //draw a new field
    game = new Game(wayTo, width, this);
    this->setFocus();
    connect(game, SIGNAL(Smove()), this, SLOT(updateCountOfMoves()));
    connect(game, SIGNAL(click()), this, SLOT(setFocus()));
    updateCountOfMoves();

    photoLayout->addWidget(game);

    //installing a hint (original photo) for easy mode
    if (!hardMode)
    {
        QPixmap img(wayTo+"0.jpg");

        img=img.scaled(600,600);
        ui->originalPhoto->setPixmap(img);

        photoLayout->addWidget(ui->originalPhoto);
    }

    layout->addLayout(photoLayout);
    counter=new QHBoxLayout;

    counter->addWidget(ui->countMoves);
    counter->addWidget(ui->countTime);
    ui->countTime->setText("Time: 00:00:00");
    connect(this->timer, SIGNAL(timeout()), this, SLOT(setTime()));
    layout->addLayout(counter);
    layout->update();

    game->show();

    resize(sizeHint());
}


/*
    Back to the mainwindow

    @param -
    @return -
*/
void Form::on_ExitGame_clicked()
{
    MainWindow *f = new MainWindow();
    f->show();
    this->close();
    this->~Form();
}

/*
    On CnangePhoto clicked

    @param -
    @return -
*/
void Form::on_CnangePhoto_clicked()
{
    //opens a folder with pictures
    QDir dir=QDir::current();
    dir.cdUp();
    dir.cd("pictures");
    this->setFocus();

    QString FileName =QFileDialog::getOpenFileName(this, tr("Open File"),dir.absolutePath(),"*.png");
    if (FileName.isEmpty())return;

    changePhoto(FileName);
}

/*
    break a picture for a puzzle

    @param QString
    @return -
*/
void Form::changePhoto(QString FileName)
{
    QImage* original=new QImage(FileName);

    int min=qMin(original->width(), original->height());
    min=min-min%width;//make kratne width

    QImage* SquareImage=new QImage;
    *SquareImage=original->copy(0, 0,min,min);
    delete original;

    QDir dir=QDir::current();
    dir.cdUp();
    dir.cd("pictures");
    FileName=FileName.left(FileName.lastIndexOf('.'));
    FileName=FileName.right(FileName.length()-FileName.lastIndexOf('/')-1);
    while (!dir.cd(FileName+QString::number(width)))
    {
        dir.mkdir(FileName+QString::number(width));
    }
    wayTo=dir.absolutePath()+"/";


    SquareImage->save(wayTo+"0.jpg");
    int LSSize=min/width;//LittleSquareSize

    int count_squares=width*width;
    //creating width*width small photos and save their
    for (int i=1;i<count_squares;i++)
    {
        QImage* LittleSquare=new QImage;
        *LittleSquare=SquareImage->copy(((i-1)%width)*LSSize, (i-1)/width*LSSize, LSSize, LSSize);
        LittleSquare->save(wayTo+QString::number(i)+".jpg");
    }
    on_NewGame_clicked();
}
