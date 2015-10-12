#include "cludecommandpackagebuildnumber.hpp"

CLudeCommandPackageBuildNumber::CLudeCommandPackageBuildNumber():
    CLudeCommandPackage()
{
    this->addDescription(QLatin1String("update build information"));
}

void CLudeCommandPackageBuildNumber::process()
{
    QCommandLineOption build_number_increase(
                QStringList()<<"i"<<"increase",
                QCoreApplication::translate("main","increase build number by one and update 'updated' field")
                );
    this->addOption(build_number_increase);

    QCommandLineOption build_number_decrease(
                QStringList()<<"d"<<"decrease",
                                QCoreApplication::translate("main","decrease build number by one and update 'updated' field")
                );
    this->addOption(build_number_decrease);

    CLudeCommandPackage::process();
    //process all commands here
    if(this->isSet(build_number_increase)){
        this->actionBuildNumberIncrease();
    }
    else if(this->isSet(build_number_decrease)){
        this->actionBuildNumberDecrease();
    }
}

QString CLudeCommandPackageBuildNumber::name()
{
    return QLatin1String("build-number");
}

QString CLudeCommandPackageBuildNumber::version()
{
    return QLatin1String("1.0.0");
}

void CLudeCommandPackageBuildNumber::actionBuildNumberIncrease()
{
    this->updateBuildNumber(1);
}

void CLudeCommandPackageBuildNumber::actionBuildNumberDecrease()
{
    this->updateBuildNumber(-1);
}

void CLudeCommandPackageBuildNumber::updateBuildNumber(int inc)
{
    QDir vDir(QDir::currentPath());
    vDir.setNameFilters(QStringList()<<"*.pro");
    QStringList one =  vDir.entryList(QDir::Files);
    if(one.size()!=1){
        qDebug() << "No pro file found.";
        return;
    }

    QString name = one[0].replace(".pro","");
    //NOTE changed cludepackage.json to <package_name>.cde
    QString vPath = QDir::toNativeSeparators(QDir::currentPath()+QLatin1String("/")+name+QLatin1String(".cde"));
    QFile vFile(vPath);
    if(!vFile.exists()){
        qDebug() << "PATH: "<<vPath;
        qDebug() << "cludepackage.json file does not exists";
    }
    else{
        CLudePackage clp;
        if(clp.fromJsonFile(vPath)){
            clp.setUpdated(QDateTime::currentDateTime().toLocalTime());
            clp.setBuild(clp.build()+inc);
            if(clp.toJsonFile(vPath)){
                qDebug() << "build updated to :"<<clp.build();
            }
            else{
                qDebug() << "failed to update build";
            }
        }
        else{
            qDebug() << "cludepackage.json file parsing error";
        }
    }
}

