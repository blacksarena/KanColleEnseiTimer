#include "ensei_data.h"

EnseiData::EnseiData(const QString &path)
{
    QFile ensei_list(path);
    if(!ensei_list.open(QIODevice::ReadOnly)){
        qWarning("failed");
        return;
    }
    QByteArray tmp = ensei_list.readAll();
    ensei_list.close();
    _object = QJsonDocument::fromJson(tmp).object();
    parseEnseiList(_object["遠征"].toArray());
}


EnseiData::~EnseiData()
{

}

void EnseiData::parseEnseiList(const QJsonArray &array)
{
    for(int area = 0; area < array.count(); ++area){// 遠征海域
        QJsonObject ensei_area = array.at(area).toObject();
        QJsonArray ensei_array = ensei_area[ensei_area.keys().at(0)].toArray();
        for(int ensei = 0; ensei < ensei_array.count(); ++ensei){// 遠征ごと
            QJsonObject ensei_data = ensei_array.at(ensei).toObject()[ensei_array.at(ensei).toObject().keys().at(0)].toObject();
            _enseiname_list.append(ensei_data["遠征名"].toString());
            _ensei_lib[ensei_data["遠征名"].toString()] = ensei_data;
        }
    }
}


int EnseiData::getHour(const QString &ensei_name)
{
    return _ensei_lib[ensei_name]["必要時間"].toObject()["時間"].toInt();
}

int EnseiData::getMin(const QString &ensei_name)
{
    return _ensei_lib[ensei_name]["必要時間"].toObject()["分"].toInt();
}

int EnseiData::getFuel(const QString &ensei_name)
{
    return _ensei_lib[ensei_name]["獲得資源"].toObject()["燃料"].toInt();
}

int EnseiData::getAmmunition(const QString &ensei_name)
{
    return _ensei_lib[ensei_name]["獲得資源"].toObject()["弾薬"].toInt();
}

int EnseiData::getSteel(const QString &ensei_name)
{
    return _ensei_lib[ensei_name]["獲得資源"].toObject()["鋼材"].toInt();
}

int EnseiData::getBauxite(const QString &ensei_name)
{
    return _ensei_lib[ensei_name]["獲得資源"].toObject()["ボーキサイト"].toInt();
}
