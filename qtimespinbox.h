#ifndef QTIMESPINBOX_H
#define QTIMESPINBOX_H

#include <QtWidgets>


class QTimeSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    QTimeSpinBox(QWidget *parent = nullptr);

public slots:
    void loopValue(int i);
};

#endif // QTIMESPINBOX_H
