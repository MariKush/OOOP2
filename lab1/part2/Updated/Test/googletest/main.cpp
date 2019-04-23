#include <gtest/gtest.h>
#include <QApplication>

#include "form.h"
#include <QPushButton>
#include <QDir>
#include <QGridLayout>
#include <QKeyEvent>
#include <QtEvents>


TEST(Form, SettertGetters) {
  Form f;
  EXPECT_TRUE(f);
  EXPECT_TRUE(f.game);//<<"not create game in form";
  EXPECT_EQ(f.game->countMoves, 0)<<"count moves not equel 0";

}

TEST(Form, CanBeSolve) {
  Form f;

  int n=0;
  for(int i = 0; i < 16; i++)
      for(int j = 0; j < f.game->numbers.indexOf(i); j++)
      {
          if(f.game->numbers[j] < i)
          {
              ++n;
          }
      }
  EXPECT_TRUE(n%2==0)<<"cant be solve";
}

TEST(Form,MoveCells){
    Form f;

    for(int i=0;i<100000;i++)
    {

        int x, y, rs, cs;
        QPushButton* clickedBtn =f.game->buttons[qrand()%15];
        f.game->grid->getItemPosition(f.game->grid->indexOf(clickedBtn), &y, &x, &rs, &cs);

        if((f.game->path.x() == x && (f.game->path.y() == y+1 || f.game->path.y() == y-1))
        || (f.game->path.y() == y && (f.game->path.x() == x+1 || f.game->path.x() == x-1)))
        {
            int countMoves = f.game->countMoves;
            clickedBtn->click();
            EXPECT_EQ(f.game->path,QPoint(x,y));
            EXPECT_EQ(countMoves+1,f.game->countMoves);
        }
        else
        {
            int countMoves = f.game->countMoves;
            QPoint qp(f.game->path);
            clickedBtn->click();
            EXPECT_EQ(f.game->path,qp);
            EXPECT_EQ(countMoves,f.game->countMoves);
        }
    }

}

TEST(Form, ChangePhoto){
    for (int i=2;i<8;i++)
    {
        Form f(true, i);
        QDir dir=QDir::current();
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
        dir.cd("pictures");
        dir.remove("board"+QString::number(f.width));
        f.changePhoto(dir.path()+"/board.png");
        dir=QDir::current();
        dir.cdUp();
        EXPECT_TRUE(dir.cd("board"+QString::number(f.width)));
    }

}

TEST(Form, KeyClickEvent)
{
    Form f;

    for (int i=0;i<1000;i++)
    {
        int countMoves=f.game->countMoves;
        QPoint path(f.game->path);
        int key=Qt::Key_Left+qrand()%4;

        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, Qt::KeyboardModifier::NoModifier);
        if ( (key==Qt::Key_Left  && f.game->path.x()!=f.width-1)||
             (key==Qt::Key_Right && f.game->path.x()!=0)||
             (key==Qt::Key_Up    && f.game->path.y()!=f.width-1)||
             (key==Qt::Key_Down  && f.game->path.y()!=0) )
        {

            if (key==Qt::Key_Left ){
                path.setX(path.x()+1);
            }
            else if(key==Qt::Key_Right){
                path.setX(path.x()-1);
            }
            else if (key==Qt::Key_Up){
                path.setY(path.y()+1);
            }
            else if (key==Qt::Key_Down){
                path.setY(path.y()-1);
            }

            f.keyPressEvent(event);
            EXPECT_EQ(f.game->path,path);
            EXPECT_EQ(countMoves+1,f.game->countMoves);
        }
        else{

            f.keyPressEvent(event);
            EXPECT_EQ(f.game->path,path);
            EXPECT_EQ(countMoves,f.game->countMoves);
        }

    }

}

int main(int argc,char*argv[])
{
    QApplication a(argc, argv);
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();

}

