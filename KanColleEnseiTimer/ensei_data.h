#ifndef ENSEIDATA_H
#define ENSEIDATA_H

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

class EnseiData
{
public:
    EnseiData(const QString &path);
    virtual ~EnseiData();

    QString test();
    QStringList getEnseiList();
    int getHour(const QString &ensei_name);
    int getMin(const QString &ensei_name);
    int getFuel(const QString &ensei_name);
    int getAmmunition(const QString &ensei_name);
    int getSteel(const QString &ensei_name);
    int getBauxite(const QString &ensei_name);

private:
    void parseEnseiList(const QJsonArray &array);

private:
    QJsonObject _object;
    QStringList _enseiname_list;
    std::map<QString, QJsonObject> _ensei_lib;
};

#endif // ENSEIDATA_H
