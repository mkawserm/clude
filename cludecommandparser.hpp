#ifndef CLUDECOMMANDPARSER_HPP
#define CLUDECOMMANDPARSER_HPP

#include <QDir>
#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "cludecommandpackage.hpp"
#include "cludecommandpackageinit.hpp"
#include "cludecommandpackagebuildnumber.hpp"


class CLudeCommandParser
{
    private:
        QMap <QString,CLudeCommandPackage*> m_command_package_list;

    public:
        CLudeCommandParser();
        ~CLudeCommandParser();
        void process(const QStringList &arglist);
        void addCommandPackage(CLudeCommandPackage *package);

        /*
        static void initilizeProject(const QString &package,const QString &name,const QString &path);
        static void updateBuild(const QString &path);
        */
};

#endif // CLUDECOMMANDPARSER_HPP
