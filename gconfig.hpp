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

        static bool copy(const QString &source,const QString &destination,QMultiMap<quint8,QString> &message);
        static QString hash(const QString &source);
};

#endif // GCONFIG_HPP
