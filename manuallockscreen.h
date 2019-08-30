#ifndef MANUALLOCKSCREEN_H
#define MANUALLOCKSCREEN_H

#include <QtCore>
#include <QtWidgets>
#include <QDialog>

namespace Ui {
class ManualLockScreen;
}

class ManualLockScreen : public QDialog
{
    Q_OBJECT

public:
    explicit ManualLockScreen(const QRect &initRect, QWidget *parent = 0);
    ~ManualLockScreen();
    QRect gameWindowRect() const {return _gameWindowRect;}

private slots:
    void on_timer_timeout();
    void on_x_valueChanged(int x);
    void on_y_valueChanged(int y);
    void on_width_valueChanged(int width);
    void on_height_valueChanged(int height);

private:
    Ui::ManualLockScreen *ui;
    QTimer *_timer;
    QRect _gameWindowRect;
    QLabel _gameWindowImage;

    void reclipGameWindow();
};

#endif // MANUALLOCKSCREEN_H
