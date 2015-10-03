#include "cludecommandparser.hpp"

CLudeCommandParser::CLudeCommandParser()
{
    QCoreApplication::setApplicationName("clude");
    QCoreApplication::setApplicationVersion("1.0.0");

    //add all command package
    this->addCommandPackage(new CLudeCommandPackageInit());
    this->addCommandPackage(new CLudeCommandPackageBuildNumber());
}

CLudeCommandParser::~CLudeCommandParser()
{
    while(this->m_command_package_list.isEmpty()){
        delete this->m_command_package_list.take(this->m_command_package_list.keys().first());
    }
    this->m_command_package_list.clear();
}


void CLudeCommandParser::process(const QStringList &arglist)
{
    QStringList arguments = arglist;
    if(arguments.size()<2){
        qDebug() << "Available command packages: ";
        int i=1;
        foreach (const QString &key, this->m_command_package_list.keys()) {
            qDebug() <<QString("    %1.%2 :: %3").arg(i).arg(key).arg(this->m_command_package_list.value(key)->description()).toLocal8Bit().constData();
            ++i;
        }
    }
    else{
        QString ccpn = arguments.at(1);
        if(!this->m_command_package_list.contains(ccpn)){
            qDebug() << QString("%1 command package not found").arg(ccpn).toLocal8Bit().constData();
        }
        else{
            arguments.removeAt(1);
            CLudeCommandPackage *ccp = this->m_command_package_list.value(ccpn);
            ccp->setArgumentList(arguments);
            ccp->process();
        }
    }
}


void CLudeCommandParser::addCommandPackage(CLudeCommandPackage *package)
{
    if(!this->m_command_package_list.contains(package->name())){
        this->m_command_package_list.insert(package->name(),package);
    }
}
