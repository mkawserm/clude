#ifndef CLUDECOMMANDPACKAGEBUILDNUMBER_HPP
#define CLUDECOMMANDPACKAGEBUILDNUMBER_HPP

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "cludepackage.hpp"
#include "cludecommandpackage.hpp"

class CLudeCommandPackageBuildNumber : public CLudeCommandPackage
{
    public:
        CLudeCommandPackageBuildNumber();
        void process() Q_DECL_OVERRIDE;
        QString name() Q_DECL_OVERRIDE;
        QString version() Q_DECL_OVERRIDE;

        void actionBuildNumberUpdate();
};

#endif // CLUDECOMMANDPACKAGEBUILDNUMBER_HPP
