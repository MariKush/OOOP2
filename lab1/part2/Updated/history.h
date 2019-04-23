#ifndef HISTORY_H
#define HISTORY_H

/*
    K-28
    history.h
    Purpose: idescription of class History functions
    (class for visualization save history)
    @author Mariia Kushnirenko
    @version 22/04/19
*/

#include <QDialog>

namespace Ui {
class History;
}

class History : public QDialog
{
    Q_OBJECT

public:
    explicit History(QString filename, QWidget *parent = nullptr);
    ~History();

private slots:
    void on_sort_by_time_radiobtn_clicked();

    void on_sort_by_step_radiobtn_clicked();

private:
    void set_text(QString filename);
    void swap_raw(int r1, int r2);
    Ui::History *ui;
};

#endif // HISTORY_H
