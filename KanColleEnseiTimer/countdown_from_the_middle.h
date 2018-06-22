#ifndef COUNTDOWN_FROM_THE_MIDDLE_H
#define COUNTDOWN_FROM_THE_MIDDLE_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class CountdownFromTheMiddle;
}

class CountdownFromTheMiddle : public QDialog
{
    Q_OBJECT

public:
    explicit CountdownFromTheMiddle(QWidget *parent = 0);
    ~CountdownFromTheMiddle();

    inline int hour()  const{return _hour;}
    inline int minute()const{return _minute;}
    inline int second()const{return _second;}

private slots:
    void on_CountdownFromTheMiddle_accepted();

private:
    Ui::CountdownFromTheMiddle *ui;
    int _hour;
    int _minute;
    int _second;
};

#endif // COUNTDOWN_FROM_THE_MIDDLE_H
