#ifndef GCONFIG_HPP
#define GCONFIG_HPP

#include <QDir>
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
        static QString projectPriFilePath();
};

#endif // GCONFIG_HPP
