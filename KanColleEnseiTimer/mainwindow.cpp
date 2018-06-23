#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
:QMainWindow(parent)
,ui(new Ui::MainWindow)
,continue_fleet(eContinueFleetId::unknown)
{
    ui->setupUi(this);

    // 設定のロード
    _settings = new EnseiSettings("settings.ini", QSettings::IniFormat);
    this->move(_settings->windowPos());
    if(_settings->windowFrontmost() == true){
        this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    }

    _ensei_data = new EnseiData(_settings->enseiDataPath());

    _count_down[0] = new CountDownTimer();
    _count_down[1] = new CountDownTimer();
    _count_down[2] = new CountDownTimer();
    QObject::disconnect(ui->ensei_list2, SIGNAL(currentTextChanged(const QString&)), this, SLOT(on_ensei_list2_currentTextChanged(const QString&)));
    QObject::disconnect(ui->ensei_list3, SIGNAL(currentTextChanged(const QString&)), this, SLOT(on_ensei_list3_currentTextChanged(const QString&)));
    QObject::disconnect(ui->ensei_list4, SIGNAL(currentTextChanged(const QString&)), this, SLOT(on_ensei_list4_currentTextChanged(const QString&)));
    ui->ensei_list2->addItems(_ensei_data->getEnseiList());
    ui->ensei_list3->addItems(_ensei_data->getEnseiList());
    ui->ensei_list4->addItems(_ensei_data->getEnseiList());
    ui->ensei_list2->setCurrentText(_settings->destination(0));
    ui->ensei_list3->setCurrentText(_settings->destination(1));
    ui->ensei_list4->setCurrentText(_settings->destination(2));
    QObject::connect(ui->ensei_list2, SIGNAL(currentTextChanged(const QString&)), this, SLOT(on_ensei_list2_currentTextChanged(const QString&)));
    QObject::connect(ui->ensei_list3, SIGNAL(currentTextChanged(const QString&)), this, SLOT(on_ensei_list3_currentTextChanged(const QString&)));
    QObject::connect(ui->ensei_list4, SIGNAL(currentTextChanged(const QString&)), this, SLOT(on_ensei_list4_currentTextChanged(const QString&)));
    _count_down[0]->setTimer(_ensei_data->getHour(ui->ensei_list2->currentText()), _ensei_data->getMin(ui->ensei_list2->currentText()));
    _count_down[1]->setTimer(_ensei_data->getHour(ui->ensei_list3->currentText()), _ensei_data->getMin(ui->ensei_list3->currentText()));
    _count_down[2]->setTimer(_ensei_data->getHour(ui->ensei_list4->currentText()), _ensei_data->getMin(ui->ensei_list4->currentText()));
    if(_settings->enseiCounting(0) == true){
        ui->return_time2->setText(_count_down[0]->start(_settings->enseiStartDate(0)));
    }
    if(_settings->enseiCounting(1) == true){
        ui->return_time3->setText(_count_down[1]->start(_settings->enseiStartDate(1)));
    }
    if(_settings->enseiCounting(2) == true){
        ui->return_time4->setText(_count_down[2]->start(_settings->enseiStartDate(2)));
    }
    countdown_update_id = startTimer(1000);
    QTimerEvent *e = new QTimerEvent(countdown_update_id);
    timerEvent(new QTimerEvent(countdown_update_id));// 画面更新のため
    delete e;

    _screen_shot = new ScreenShot;
}

MainWindow::~MainWindow()
{
    _settings->setWindowPos(this->pos());
    _settings->setWindowFrontmost(this->windowFlags() & Qt::WindowStaysOnTopHint);
    qDebug() << (bool)(this->windowFlags() & Qt::WindowStaysOnTopHint);
    delete _ensei_data;
    delete _count_down[0];
    delete _count_down[1];
    delete _count_down[2];
    delete _settings;
    delete ui;
}


void MainWindow::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == countdown_update_id){
        if(_count_down[0]->isCountDown()){
            updateLeftTime(_count_down[0], ui->left_time2);
        }else{
            ui->left_time2->setStyleSheet("background:#E00000; color:#303030");
        }
        if(_count_down[1]->isCountDown()){
            updateLeftTime(_count_down[1], ui->left_time3);
        }else{
            ui->left_time3->setStyleSheet("background:#E00000; color:#303030");
        }
        if(_count_down[2]->isCountDown()){
            updateLeftTime(_count_down[2], ui->left_time4);
        }else{
            ui->left_time4->setStyleSheet("background:#E00000; color:#303030");
        }
    }else if(e->timerId() == continue_fleet_id){
        CountdownFromTheMiddle *p = new CountdownFromTheMiddle(this);
        switch(continue_fleet){
        case eContinueFleetId::second:
            if(p->exec() == QDialog::Accepted){
                ui->return_time2->setText(_count_down[0]->start(this->_count_down[0]->setOffsetTime(p->hour(), p->minute(), p->second())));
                _settings->setEnseiStartDate(0, _count_down[0]->startTime());
                _settings->setEnseiCounting(0, _count_down[0]->isCountDown());
                _settings->saveSettings();
            }
            break;
        case eContinueFleetId::third:
            if(p->exec() == QDialog::Accepted){
                ui->return_time3->setText(_count_down[1]->start(this->_count_down[1]->setOffsetTime(p->hour(), p->minute(), p->second())));
                updateLeftTime(_count_down[1], ui->left_time3);
                _settings->setEnseiStartDate(1, _count_down[1]->startTime());
                _settings->setEnseiCounting(1, _count_down[1]->isCountDown());
                _settings->saveSettings();
            }
            break;
        case eContinueFleetId::fourth:
            if(p->exec() == QDialog::Accepted){
                ui->return_time4->setText(_count_down[2]->start(this->_count_down[2]->setOffsetTime(p->hour(), p->minute(), p->second())));
                updateLeftTime(_count_down[2], ui->left_time4);
                _settings->setEnseiStartDate(2, _count_down[2]->startTime());
                _settings->setEnseiCounting(2, _count_down[2]->isCountDown());
                _settings->saveSettings();
            }
            break;
        default:
            break;
        }
        delete p;
        continue_fleet = eContinueFleetId::unknown;
        killTimer(continue_fleet_id);
    }
}

void MainWindow::on_ensei_list2_currentTextChanged(const QString &arg1)
{
    _count_down[0]->stop();
    _count_down[0]->setTimer(_ensei_data->getHour(arg1), _ensei_data->getMin(arg1));
    updateLeftTime(_count_down[0], ui->left_time2);

    // change resource
    ui->fuel2->setText(QString::number(_ensei_data->getFuel(arg1)));
    ui->ammunition2->setText(QString::number(_ensei_data->getAmmunition(arg1)));
    ui->steel2->setText(QString::number(_ensei_data->getSteel(arg1)));
    ui->bauxite2->setText(QString::number(_ensei_data->getBauxite(arg1)));
    _settings->setDestination(0, arg1);
    _settings->setEnseiCounting(0, _count_down[0]->isCountDown());
    _settings->saveSettings();
}

void MainWindow::on_ensei_list3_currentTextChanged(const QString &arg1)
{
    _count_down[1]->stop();
    _count_down[1]->setTimer(_ensei_data->getHour(arg1), _ensei_data->getMin(arg1));
    updateLeftTime(_count_down[1], ui->left_time3);

    // change resource
    ui->fuel3->setText(QString::number(_ensei_data->getFuel(arg1)));
    ui->ammunition3->setText(QString::number(_ensei_data->getAmmunition(arg1)));
    ui->steel3->setText(QString::number(_ensei_data->getSteel(arg1)));
    ui->bauxite3->setText(QString::number(_ensei_data->getBauxite(arg1)));
    _settings->setDestination(1, arg1);
    _settings->setEnseiCounting(1, _count_down[1]->isCountDown());
    _settings->saveSettings();
}

void MainWindow::on_ensei_list4_currentTextChanged(const QString &arg1)
{
    _count_down[2]->stop();
    _count_down[2]->setTimer(_ensei_data->getHour(arg1), _ensei_data->getMin(arg1));
    updateLeftTime(_count_down[2], ui->left_time4);

    // change resource
    ui->fuel4->setText(QString::number(_ensei_data->getFuel(arg1)));
    ui->ammunition4->setText(QString::number(_ensei_data->getAmmunition(arg1)));
    ui->steel4->setText(QString::number(_ensei_data->getSteel(arg1)));
    ui->bauxite4->setText(QString::number(_ensei_data->getBauxite(arg1)));
    _settings->setDestination(2, arg1);
    _settings->setEnseiCounting(2, _count_down[2]->isCountDown());
    _settings->saveSettings();
}

void MainWindow::on_departure2_clicked()
{
    killTimer(continue_fleet_id);
    _count_down[0]->setTimer(_ensei_data->getHour(ui->ensei_list2->currentText()),
                             _ensei_data->getMin(ui->ensei_list2->currentText()));
    ui->return_time2->setText(_count_down[0]->start());
    updateLeftTime(_count_down[0], ui->left_time2);
    ui->left_time2->setStyleSheet("");
    _settings->setEnseiStartDate(0, _count_down[0]->startTime());
    _settings->setEnseiCounting(0, _count_down[0]->isCountDown());
    _settings->saveSettings();
    // timer kill
}

void MainWindow::on_departure3_clicked()
{
    killTimer(continue_fleet_id);
    _count_down[1]->setTimer(_ensei_data->getHour(ui->ensei_list3->currentText()),
                             _ensei_data->getMin(ui->ensei_list3->currentText()));
    ui->return_time3->setText(_count_down[1]->start());
    updateLeftTime(_count_down[1], ui->left_time3);
    ui->left_time3->setStyleSheet("");
    _settings->setEnseiStartDate(1, _count_down[1]->startTime());
    _settings->setEnseiCounting(1, _count_down[1]->isCountDown());
    _settings->saveSettings();
}
void MainWindow::on_departure4_clicked()
{
    killTimer(continue_fleet_id);
    _count_down[2]->setTimer(_ensei_data->getHour(ui->ensei_list4->currentText()),
                             _ensei_data->getMin(ui->ensei_list4->currentText()));
    ui->return_time4->setText(_count_down[2]->start());
    updateLeftTime(_count_down[2], ui->left_time4);
    ui->left_time4->setStyleSheet("");
    _settings->setEnseiStartDate(2, _count_down[2]->startTime());
    _settings->setEnseiCounting(2, _count_down[2]->isCountDown());
    _settings->saveSettings();
}

void MainWindow::on_foremost_triggered()
{
    if(ui->foremost->isChecked()){
        this->setWindowFlags(Qt::WindowStaysOnTopHint);
        this->show();
    }else{
        this->setWindowFlags(this->windowFlags() ^ Qt::WindowStaysOnTopHint);
    }
}

void MainWindow::updateLeftTime(CountDownTimer *timer, QLabel *left_time)
{
    QString left_time_regexp;// 正規表現
    int left_time_sec = timer->getLeftTime();
    left_time_regexp.sprintf("%02d:%02d:%02d", left_time_sec / 3600,
                                            (left_time_sec % 3600) / 60,
                                            left_time_sec % 60);
    left_time->setText(left_time_regexp);
    if(left_time_sec < 1){
        timer->stop();
    }
    if(left_time_sec < 60){
        left_time->setStyleSheet("background:#E00000; color:#303030");// FF0000の赤は明るすぎる
    }else if(timer->isCountDown()){
        left_time->setStyleSheet("");
    }
}

void MainWindow::on_departure2_released()
{
    qDebug() << "release";
}

void MainWindow::on_departure3_released()
{

}

void MainWindow::on_departure4_released()
{

}

void MainWindow::on_pushButton_clicked()
{
    _screen_shot->serchGameWindow();
}

void MainWindow::on_format_png_toggled(bool status)
{
    if(status == true){
        ui->format_jpg->setChecked(false);
        ui->format_bmp->setChecked(false);
        _screen_shot->setFormat(ImageFormat::png);
    }
}

void MainWindow::on_format_jpg_toggled(bool status)
{
    if(status == true){
        ui->format_png->setChecked(false);
        ui->format_bmp->setChecked(false);
        _screen_shot->setFormat(ImageFormat::jpg);
    }
}

void MainWindow::on_format_bmp_toggled(bool status)
{
    if(status == true){
        ui->format_png->setChecked(false);
        ui->format_bmp->setChecked(false);
        _screen_shot->setFormat(ImageFormat::bmp);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    _screen_shot->takeScreenShot();
}

void MainWindow::on_departure2_pressed()
{
    qDebug() << "pressed";
    // timer start
    continue_fleet_id = this->startTimer(500);
    continue_fleet = eContinueFleetId::second;
}

void MainWindow::on_departure3_pressed()
{
    continue_fleet_id = this->startTimer(500);
    continue_fleet = eContinueFleetId::third;
}

void MainWindow::on_departure4_pressed()
{
    continue_fleet_id = this->startTimer(500);
    continue_fleet = eContinueFleetId::fourth;
}

void MainWindow::on_info2_clicked()
{
    showEnseiInfo(ui->ensei_list2->currentText());
}

void MainWindow::on_info3_clicked()
{
    showEnseiInfo(ui->ensei_list3->currentText());
}

void MainWindow::on_info4_clicked()
{
    showEnseiInfo(ui->ensei_list4->currentText());
}

void MainWindow::showEnseiInfo(const QString &ensei_name)
{
    QMessageBox msg_box(this);
    QStringList info = _ensei_data->getEnseiInfo(ensei_name);
    QString new_line;
#ifdef __linux__
    new_line = "\n";
#elif _WIN32
    new_line = "\r\n";
#elif __APPLE__
    new_line = "\n";
#endif
    QString msg_text = info[eInfo::required_organization] + new_line +
                       info[eInfo::required_shiptype] + new_line +
                       info[eInfo::other_info] + new_line +
                       info[eInfo::composition_example];
    msg_box.setText(msg_text);
    msg_box.setWindowTitle("information");
    msg_box.setStandardButtons(QMessageBox::Ok);
    msg_box.setDefaultButton(QMessageBox::Ok);
    msg_box.exec();
}
