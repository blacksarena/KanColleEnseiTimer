#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtWidgets/QtWidgets>
#include "ensei_data.h"
#include "count_down_timer.h"
#include "ensei_settings.h"
#include "screen_shot.h"
#include "countdown_from_the_middle.h"
#include "manuallockscreen.h"

enum eContinueFleetId{
    unknown = 0,
    second,
    third,
    fourth
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void timerEvent(QTimerEvent *e);

private:
    void updateLeftTime(CountDownTimer *timer, QLabel *left_time);
    void showEnseiInfo(const QString &ensei_name);
    void countDownDock(int dock_index, QTimeEdit *widget);

private slots:
    void on_ensei_list2_currentTextChanged(const QString &arg1);
    void on_ensei_list3_currentTextChanged(const QString &arg1);
    void on_ensei_list4_currentTextChanged(const QString &arg1);
    void on_departure2_clicked();
    void on_departure3_clicked();
    void on_departure4_clicked();
    void on_foremost_triggered();
    void on_departure2_released();
    void on_departure3_released();
    void on_departure4_released();
    void on_serchWindow_clicked();
    void on_format_png_toggled(bool status);
    void on_format_jpg_toggled(bool status);
    void on_format_bmp_toggled(bool status);
    void on_takeSS_clicked();
    void on_departure2_pressed();
    void on_departure3_pressed();
    void on_departure4_pressed();
    void on_info2_clicked();
    void on_info3_clicked();
    void on_info4_clicked();
    void on_adjust_screen_triggered();
    void on_checkSS_clicked();
    void on_enterDock1_clicked();
    void on_enterDock2_clicked();
    void on_enterDock3_clicked();
    void on_enterDock4_clicked();

private:
    Ui::MainWindow *ui;
    EnseiData *_ensei_data;
    CountDownTimer *_count_down[3];
    bool _is_countdown_dock[4];
    EnseiSettings *_settings;
    ScreenShot *_screen_shot;
    int countdown_update_id;
    int continue_fleet_id;
    eContinueFleetId continue_fleet;
};

#endif // MAINWINDOW_H
