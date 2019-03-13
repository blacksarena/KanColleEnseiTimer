#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

#include <QDateTime>
#include <QDebug>

class CountDownTimer
{
public:
    CountDownTimer();

    void setTimer(int hour, int min, int sec = 0);
    QString start(QDateTime start_time = QDateTime::currentDateTime());
    void stop();
    int getLeftTime();// return sec
    inline bool isCountDown()const{return _counting;}
    inline QDateTime startTime(){return _end_time.addSecs(-(_hour*3600+_min*60));}
    inline const QString year()  {return _end_time.addSecs(-(_hour*3600+_min*60)).toString("yyyy");}
    inline const QString month() {return _end_time.addSecs(-(_hour*3600+_min*60)).toString("MM");}
    inline const QString day()   {return _end_time.addSecs(-(_hour*3600+_min*60)).toString("dd");}
    inline const QString hour()  {return _end_time.addSecs(-(_hour*3600+_min*60)).toString("hh");}
    inline const QString minute(){return _end_time.addSecs(-(_hour*3600+_min*60)).toString("mm");}
    inline const QString second(){return _end_time.addSecs(-(_hour*3600+_min*60)).toString("ss");}
    QDateTime setOffsetTime(int hour, int min, int sec);

private:
    bool _counting;
    int _hour;
    int _min;
    int _sec;
    QDateTime _end_time;
};

#endif // COUNTDOWNTIMER_H
