#ifndef GCONFIG_HPP
#define GCONFIG_HPP

#include <QFile>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCoreApplication>

class GConfig
{
    public:
        GConfig();

        static QString repoPath();
};

#endif // GCONFIG_HPP
