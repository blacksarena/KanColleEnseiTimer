#include "ensei_settings.h"


EnseiSettings::EnseiSettings(const QString &fileName, QSettings::Format format, QObject *parent)
:QSettings(fileName, format, parent)
,_fleet_2nd(0)// 配列の位置指定に使うため、ひとつずつずれている
,_fleet_3rd(1)
,_fleet_4th(2)
,_fleet_number({"fleet_2nd", "fleet_3rd", "fleet_4th"})
{
    loadSettings();
}

EnseiSettings::~EnseiSettings()
{
    saveSettings();
}

// private functions
void EnseiSettings::loadSettings()
{
    this->beginGroup("window");
    _ensei_data_path  = this->value("ensei_data_path", "").toString();
    _window_pos.rx()  = this->value("window_pos_x", 0).toInt();
    _window_pos.ry()  = this->value("window_pos_y", 0).toInt();
    _window_frontmost = this->value("window_frontmost", false).toBool();
    this->endGroup();

    loadEnseiInfo(_fleet_2nd);
    loadEnseiInfo(_fleet_3rd);
    loadEnseiInfo(_fleet_4th);
}

void EnseiSettings::loadEnseiInfo(int fleet_number)
{
    this->beginGroup(_fleet_number[fleet_number]);
    _destination[fleet_number] = this->value("destination", "").toString();
    _ensei_start_date[fleet_number] = QDateTime::fromString(this->value("year",  "").toString()+
                                                            this->value("month", "").toString()+
                                                            this->value("day",   "").toString()+
                                                            this->value("hour",  "").toString()+
                                                            this->value("minute","").toString()+
                                                            this->value("second","").toString(),
                                                            "yyyyMMddhhmmss");
    _ensei_counting[fleet_number] = this->value("counting", false).toBool();
    this->endGroup();
}

void EnseiSettings::saveSettings()
{
    this->beginGroup("window");
    this->setValue("window_pos_x", _window_pos.rx());
    this->setValue("window_pos_y", _window_pos.ry());
    this->setValue("window_frontmost", _window_frontmost);
    this->endGroup();

    saveEnseiInfo(_fleet_2nd);
    saveEnseiInfo(_fleet_3rd);
    saveEnseiInfo(_fleet_4th);
}

void EnseiSettings::saveEnseiInfo(int fleet_number)
{
    this->beginGroup(_fleet_number[fleet_number]);
    this->setValue("destination", _destination[fleet_number]);
    this->setValue("year",        _ensei_start_date[fleet_number].toString("yyyy"));
    this->setValue("month",       _ensei_start_date[fleet_number].toString("MM"));
    this->setValue("day",         _ensei_start_date[fleet_number].toString("dd"));
    this->setValue("hour",        _ensei_start_date[fleet_number].toString("hh"));
    this->setValue("minute",      _ensei_start_date[fleet_number].toString("mm"));
    this->setValue("second",      _ensei_start_date[fleet_number].toString("ss"));
    this->setValue("counting",    _ensei_counting[fleet_number]);
    this->endGroup();
}
