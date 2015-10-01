#include "cludecommandpackagebuildnumber.hpp"

CLudeCommandPackageBuildNumber::CLudeCommandPackageBuildNumber():
    CLudeCommandPackage()
{
    this->addDescription(QLatin1String("update build information"));
}

void CLudeCommandPackageBuildNumber::process()
{

    CLudeCommandPackage::process();
    //process all commands here
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

void CLudeCommandPackageBuildNumber::actionBuildNumberUpdate()
{

}

void CLudeCommandPackageBuildNumber::updateBuildNumber(int inc)
{
    QString path = QDir::currentPath();
    if(path.isEmpty()){
        qDebug() << "Application path cannot be empty";
        return;
    }

    QString vPath = QDir::toNativeSeparators(path+QLatin1String("/cludepackage.json"));
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

