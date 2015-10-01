#include "cludecommandpackageinit.hpp"

CLudeCommandPackageInit::CLudeCommandPackageInit():
    CLudeCommandPackage()
{
    this->addDescription(QLatin1String("initilize various things"));

}


void CLudeCommandPackageInit::process()
{

    //initilize package action
    QCommandLineOption action_init_package(
                QStringList()<<"p"<<"package",
                QCoreApplication::translate("main", "initilize project inside the <name> folder"),
                QCoreApplication::translate("main","name")
                );
    this->addOption(action_init_package);

    CLudeCommandPackage::process();
    if(this->isSet(action_init_package)){
        QString package = this->value(action_init_package);
        this->actionInitPackage(package);
    }
}

QString CLudeCommandPackageInit::name()
{
    return "init";
}

QString CLudeCommandPackageInit::version()
{
    return "1.0.0";
}

void CLudeCommandPackageInit::actionInitPackage(const QString &package)
{
    qDebug() << "initilizing package "<<package<<" ...";
}
