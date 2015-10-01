#include "cludecommandparser.hpp"

CLudeCommandParser::CLudeCommandParser()
{
    QCoreApplication::setApplicationName("clude");
    QCoreApplication::setApplicationVersion("1.0.0");

    //add all command package
    this->addCommandPackage(new CLudeCommandPackageInit());
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
            qDebug() <<QString("    %1.%2").arg(i).arg(key).toLocal8Bit().constData();
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

/*
void CLudeCommandParser::initilizeProject(const QString &package, const QString &name, const QString &path)
{
    QString message = QString("initilizing the project inside the package '%1' folder").arg(package);
    qDebug() << message;

    CLudePackage vNewPackage;
    vNewPackage.setAuthor(QLatin1String("Your Name"));
    vNewPackage.setName(name);
    vNewPackage.setVersion(QLatin1String("1.0.0"));
    vNewPackage.setBuild(0);
    vNewPackage.setPackage(package);

    vNewPackage.setGroup(QLatin1String("Project Group"));
    vNewPackage.setCreated(QDateTime::currentDateTime().toLocalTime());
    vNewPackage.setUpdated(QDateTime::currentDateTime().toLocalTime());
    vNewPackage.setDescription(QLatin1String("Project description"));

    vNewPackage.addTag("tag1");
    vNewPackage.addTag("tag2");

    vNewPackage.addUrl("download","http://");
    vNewPackage.addUrl("documentation","http://");
    vNewPackage.addUrl("author","http://");
    //vNewPackage.addUrl("web","http://");

    vNewPackage.addQdependency("core");
    vNewPackage.addQdependency("gui");

    vNewPackage.addDependency(CLudePackageDependency("package1","name1",">=","1.0.0"));
    vNewPackage.addDependency(CLudePackageDependency("package2","name2",">=","2.0.0"));

    if(vNewPackage.toJsonFile(path)){
        qDebug() << "Project successfully initilized...";
    }
    else{
        qDebug() << "Failed to initilize project";
    }
}

void CLudeCommandParser::updateBuild(const QString &path)
{
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
            clp.setBuild(clp.build()+1);
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
*/
