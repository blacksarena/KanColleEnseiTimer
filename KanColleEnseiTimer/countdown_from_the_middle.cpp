#include "countdown_from_the_middle.h"
#include "ui_countdown_from_the_middle.h"

CountdownFromTheMiddle::CountdownFromTheMiddle(QWidget *parent)
:QDialog(parent)
,ui(new Ui::CountdownFromTheMiddle)
,_hour(0)
,_minute(0)
,_second(0)
{
    ui->setupUi(this);
}

CountdownFromTheMiddle::~CountdownFromTheMiddle()
{
    delete ui;
}

void CountdownFromTheMiddle::on_CountdownFromTheMiddle_accepted()
{
    _hour   = ui->hour->value();
    _minute = ui->minute->value();
    _second = ui->second->value();
}
