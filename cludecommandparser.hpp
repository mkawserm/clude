#ifndef CLUDECOMMANDPARSER_HPP
#define CLUDECOMMANDPARSER_HPP

#include <iostream>
#include <QDir>
#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>


#include "cludepackage.hpp"


class CLudeCommandParser
{
    private:
        QCommandLineParser m_parser;

    public:
        CLudeCommandParser();
        void process(const QStringList &argl);

        static void initilizeProject(const QString &package,const QString &name,const QString &path);
        static void updateBuild(const QString &path);
};

#endif // CLUDECOMMANDPARSER_HPP
