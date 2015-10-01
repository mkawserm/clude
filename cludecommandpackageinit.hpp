#ifndef CLUDECOMMANDPACKAGEINIT_HPP
#define CLUDECOMMANDPACKAGEINIT_HPP

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "cludecommandpackage.hpp"


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
        void actionInitPackage(const QString &package);
};

#endif // CLUDECOMMANDPACKAGEINIT_HPP
