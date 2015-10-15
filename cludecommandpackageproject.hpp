#ifndef CLUDECOMMANDPACKAGEPROJECT_HPP
#define CLUDECOMMANDPACKAGEPROJECT_HPP

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QStringList>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "gconfig.hpp"
#include "cludepackage.hpp"
#include "cludecommandpackage.hpp"
#include "cludedependencyresolver.hpp"

class CLudePackage;
class CLudeCommandPackage;
class CLudeDependencyResolver;
class CLudeCommandPackageProject;


class CLudeCommandPackageProject :public CLudeCommandPackage
{
    public:
        CLudeCommandPackageProject();
        void process() Q_DECL_OVERRIDE;
        QString name() Q_DECL_OVERRIDE;
        QString version() Q_DECL_OVERRIDE;

        ///////////////////////////////////////////////////////////////////////////////////////////
        /// \brief actionSave
        ///
        /// save the project to local repository
        ///////////////////////////////////////////////////////////////////////////////////////////
        void actionSave();

        ///////////////////////////////////////////////////////////////////////////////////////////
        /// \brief actionResolve
        ///
        /// resolve project dependencies. It will look into the local repository folder for
        /// the packages and copy into the current project folder and notify about missing packages
        ///////////////////////////////////////////////////////////////////////////////////////////
        void actionResolve();

        ///////////////////////////////////////////////////////////////////////////////////////////
        /// \brief actionListFiles
        ///
        /// list all files of current folder and sub folders
        ///////////////////////////////////////////////////////////////////////////////////////////
        void actionListFiles();


        bool copyRecursively(const QString &srcFilePath,const QString &tgtFilePath);
        QString getConfigJson(const QString &key);

        void walk(const QString &path, QStringList &files, const QStringList &exclude);

        ///////////////////////////////////////////////////////////////////////////////////////////
        /// \brief getCLudePackageFilePath
        /// \return
        ///
        /// find out clude package file <*.cde> from current package
        ///////////////////////////////////////////////////////////////////////////////////////////
        QString getCLudePackageFilePath();
};

#endif // CLUDECOMMANDPACKAGEPROJECT_HPP
