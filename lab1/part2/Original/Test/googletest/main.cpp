#include <gtest/gtest.h>
#include <QApplication>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(false) << "smile";
}

int main(int argc,char*argv[])
{
    QApplication a(argc, argv);

    return RUN_ALL_TESTS();

}

