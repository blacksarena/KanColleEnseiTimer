#ifndef ENSEI_SETTINGS_H
#define ENSEI_SETTINGS_H

#include <QtCore/QtCore>
#include <QDebug>

class EnseiSettings : public QSettings
{
public:
    EnseiSettings(const QString &fileName, QSettings::Format format, QObject *parent = nullptr);
    virtual ~EnseiSettings();

    void loadSettings();
    void saveSettings();

    inline QString   enseiDataPath(){return _ensei_data_path;}
    inline void      getEnseiDataPath(QString path){_ensei_data_path = path;}
    inline QPoint    windowPos(){return _window_pos;}
    inline void      setWindowPos(QPoint pos){_window_pos = pos;}
    inline bool      windowFrontmost(){return _window_frontmost;}
    inline void      setWindowFrontmost(bool frontmost){_window_frontmost = frontmost;}
    inline QString   destination(int fleet_number){return _destination[fleet_number];}
    inline void      setDestination(int fleet_number, const QString &destination){_destination[fleet_number] = destination;}
    inline QDateTime enseiStartDate(int fleet_number){return _ensei_start_date[fleet_number];}
    inline void      setEnseiStartDate(int fleet_number, const QDateTime &ensei_start_date){_ensei_start_date[fleet_number] = ensei_start_date;}
    inline bool      enseiCounting(int fleet_number){return _ensei_counting[fleet_number];}
    inline void      setEnseiCounting(int fleet_number, bool ensei_counting){_ensei_counting[fleet_number] = ensei_counting;}

private:
    void loadEnseiInfo(int fleet_number);
    void saveEnseiInfo(int fleet_number);

private:
    const int _fleet_2nd;
    const int _fleet_3rd;
    const int _fleet_4th;
    const QStringList _fleet_number;
    QString _ensei_data_path;
    QPoint _window_pos;
    bool _window_frontmost;
    QString _destination[3];
    QDateTime _ensei_start_date[3];
    bool _ensei_counting[3];
};

#endif // ENSEI_SETTINGS_H
