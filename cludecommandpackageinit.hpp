#ifndef CLUDECOMMANDPACKAGEINIT_HPP
#define CLUDECOMMANDPACKAGEINIT_HPP

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


class CLudePackage;
class CLudeCommandPackage;
class CLudeCommandPackageInit;


class CLudeCommandPackageInit : public CLudeCommandPackage
{
    public:
        CLudeCommandPackageInit();

        void process() Q_DECL_OVERRIDE;
        QString name() Q_DECL_OVERRIDE;
        QString version() Q_DECL_OVERRIDE;

        ///////////////////////////////////////////////////////////////////////////////////////////
        /// \brief actionInitProject
        ///
        /// when init <package> is called initlize the project in the working directory
        ///////////////////////////////////////////////////////////////////////////////////////////
        void actionInitPackage(const QString &pkg);

        void makeCludePackageJsonFile(const QString &package,const QString &name,const QString &path);
};

#endif // CLUDECOMMANDPACKAGEINIT_HPP
