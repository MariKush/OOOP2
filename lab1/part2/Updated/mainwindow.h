#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
    K-28
    mainwindow.h
    Purpose: idescription of class MainWindow functions
    (initial game window)
    @author Mariia Kushnirenko
    @version 22/04/19
*/

#include <QMainWindow>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_history_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
