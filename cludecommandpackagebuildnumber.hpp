#ifndef CLUDECOMMANDPACKAGEBUILDNUMBER_HPP
#define CLUDECOMMANDPACKAGEBUILDNUMBER_HPP

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QStringList>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "cludepackage.hpp"
#include "cludecommandpackage.hpp"

class CLudePackage;
class CLudeCommandPackage;
class CLudeCommandPackageBuildNumber;

class CLudeCommandPackageBuildNumber : public CLudeCommandPackage
{
    public:
        CLudeCommandPackageBuildNumber();
        void process() Q_DECL_OVERRIDE;
        QString name() Q_DECL_OVERRIDE;
        QString version() Q_DECL_OVERRIDE;

        void actionBuildNumberIncrease();
        void actionBuildNumberDecrease();

        void updateBuildNumber(int inc);
};

#endif // CLUDECOMMANDPACKAGEBUILDNUMBER_HPP
