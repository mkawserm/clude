#ifndef CLUDEOBJECT_HPP
#define CLUDEOBJECT_HPP

#include <iostream>
#include <QDir>
#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>


class CLudeObject
{
    private:
        QCommandLineParser m_parser;

    public:
        CLudeObject();
        void process(const QStringList &argl);

        static void initilizeProject(const QString &package);
};

#endif // CLUDEOBJECT_HPP
