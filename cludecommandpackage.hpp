#ifndef CLUDECOMMANDPACKAGE_HPP
#define CLUDECOMMANDPACKAGE_HPP

#include <QString>
#include <QStringList>
#include <QCommandLineParser>
#include <QCommandLineOption>

class CLudeCommandPackage
{
    private:
        QStringList m_argument_list;
        QCommandLineParser m_parser;

    protected:
        CLudeCommandPackage();

    public:
        void setArgumentList(const QStringList &aglist);
        void addOption(const QCommandLineOption &option);
        void addDescription(const QString &des);

        bool isSet(const QCommandLineOption &option);
        QString value(const QCommandLineOption &option);
        QStringList values(const QCommandLineOption &option);

        virtual void process()=0;
        virtual QString name()=0;
        virtual QString version()=0;
};

#endif // CLUDECOMMANDPACKAGE_HPP
