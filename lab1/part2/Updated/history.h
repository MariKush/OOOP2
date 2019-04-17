#ifndef HISTORY_H
#define HISTORY_H

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

private:
    void set_text(QString filename);
    Ui::History *ui;
};

#endif // HISTORY_H
