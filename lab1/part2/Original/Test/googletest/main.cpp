#include <gtest/gtest.h>
#include <QApplication>

#include <form.h>
#include <QPushButton>
#include <QGridLayout>

TEST(Form, SettertGetters) {
  Form f;
  //EXPECT_TRUE(f.game);//<<"not create game in form";
  //EXPECT_EQ(f.game->countMoves, 0)<<"count moves not equel 0";

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
            QPoint qp(f.game->path);
            clickedBtn->click();
            EXPECT_EQ(f.game->path,qp);
        }
    }

}


int main(int argc,char*argv[])
{
    QApplication a(argc, argv);
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();

}

