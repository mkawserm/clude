#ifndef GCONFIG_HPP
#define GCONFIG_HPP

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QMultiMap>
#include <QJsonArray>
#include <QStringList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCoreApplication>
#include <QCryptographicHash>


class GConfig
{
    public:
        GConfig();

        static QString repoPath();
        static QString projectPriFilePath();

        ///////////////////////////////////////////////////////////////////////////////////////////
        /// \brief projectFileList
        /// \return
        ///
        /// all available files of the project
        ///////////////////////////////////////////////////////////////////////////////////////////
        static QStringList projectFileList();

        static void copy(const QString &source,const QString &destination,quint8 &status);
        static QString hash(const QString &source);
};

#endif // GCONFIG_HPP
