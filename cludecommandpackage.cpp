#include "cludecommandpackage.hpp"

CLudeCommandPackage::CLudeCommandPackage()
{
    this->m_parser.addHelpOption();
}

void CLudeCommandPackage::setArgumentList(const QStringList &aglist)
{
    this->m_argument_list = aglist;
}

void CLudeCommandPackage::addOption(const QCommandLineOption &option)
{
    this->m_parser.addOption(option);
}

void CLudeCommandPackage::addDescription(const QString &des)
{
    this->m_parser.setApplicationDescription(des);
}

QString CLudeCommandPackage::description() const
{
    return this->m_parser.applicationDescription();
}

bool CLudeCommandPackage::isSet(const QCommandLineOption &option)
{
    return this->m_parser.isSet(option);
}

QString CLudeCommandPackage::value(const QCommandLineOption &option)
{
    return this->m_parser.value(option);
}

QStringList CLudeCommandPackage::values(const QCommandLineOption &option)
{
    return this->m_parser.values(option);
}

void CLudeCommandPackage::process()
{
    this->m_parser.process(this->m_argument_list);
}
