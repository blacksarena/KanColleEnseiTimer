#include "qtimespinbox.h"

QTimeSpinBox::QTimeSpinBox(QWidget *parent)
:QSpinBox(parent)
{
    this->setMaximum(60);
    this->setMinimum(-1);
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(loopValue(int)));
}

void QTimeSpinBox::loopValue(int i)
{
    if(i > 59){
        this->setValue(0);
    }else if(i < 0){
        this->setValue(59);
    }
}
