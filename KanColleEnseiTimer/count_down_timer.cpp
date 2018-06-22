#include "count_down_timer.h"

CountDownTimer::CountDownTimer()
:_counting(false)
,_end_time(QDateTime::currentDateTime())
,_hour(0)
,_min(0)
,_sec(0)
{
}

void CountDownTimer::setTimer(int hour, int min, int sec)
{
    _hour = hour;
    _min = min;
    _sec = sec;
}

QString CountDownTimer::start(QDateTime start_time)
{
    _end_time = start_time;
    _end_time = _end_time.addSecs(_hour * 3600 + _min * 60 + _sec);
    _counting = true;
    // 0以下なら現在時刻にする処理を追加
    if(_end_time.secsTo(QDateTime::currentDateTime()) > 0){
        _end_time = QDateTime::currentDateTime();
        _counting = false;
    }
    return _end_time.toString("MM/dd hh:mm");
}

void CountDownTimer::stop()
{
    _counting = false;
}

int CountDownTimer::getLeftTime()
{
    if(_counting){
        return QDateTime::currentDateTime().secsTo(_end_time);
    }else{
        return _hour * 3600 + _min * 60;
    }
}

QDateTime CountDownTimer::setOffsetTime(int hour, int min, int sec)
{
    _end_time = QDateTime::currentDateTime().addSecs(-((_hour-hour)*3600 + (_min-min)*60 +(_sec-sec)));
    qDebug() << _end_time;
    qDebug() << _hour << _min << _sec;
    qDebug() << -((_hour-hour)*3600 + (_min-min)*60 +(_sec-sec));
    return _end_time;
}
