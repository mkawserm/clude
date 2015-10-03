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

void CLudeCommandPackageInit::actionInitPackage(const QString &pkg)
{
    qDebug() << "initilizing package "<<pkg<<" ...";
    QDir vDir(QDir::currentPath());
    vDir.setNameFilters(QStringList()<<"*.pro");
    QStringList one =  vDir.entryList(QDir::Files);
    if(one.size()==1){
        QString package = pkg;
        QString path = QDir::toNativeSeparators(QDir::currentPath()+QLatin1String("/cludepackage.json"));
        QString pro = QDir::toNativeSeparators(QDir::currentPath()+QLatin1String("/")+one[0]);
        QString name = one[0].replace(".pro","");
        QString pri = QDir::toNativeSeparators(QDir::currentPath()+QLatin1String("/")+name+QLatin1String(".pri"));
        this->makeCludePackageJsonFile(package,name,path);
        QFile vPriFile(pri);
        if(!vPriFile.exists()){
            if(vPriFile.open(QIODevice::WriteOnly|QIODevice::Text)){
                vPriFile.write("SOURCES += \\");
                vPriFile.write("\n");

                vPriFile.write("HEADERS += \\");
                vPriFile.write("\n");

                vPriFile.write("FORMS += \\");
                vPriFile.write("\n");

                vPriFile.write("RESOURCES += \\");
                vPriFile.write("\n");

                vPriFile.write("DISTFILES += \\");

                vPriFile.close();
                qDebug() << pri<< "file created";
            }
        }

        //now include it to the pro file
        qDebug() << "pro file:"<<pro;
        QFile vProFile(pro);
        if(vProFile.open(QIODevice::Append|QIODevice::Text)){
            vProFile.seek(vProFile.size());
            vProFile.write("\n");
            vProFile.write(QString("include(%1)").arg(name+QLatin1String(".pri")).toLocal8Bit());
            vProFile.close();
            qDebug() << "pri file included to the pro file";
        }
        else{
            qDebug() << "failed to open "<<pro<<" file";
        }

    }
    else{
        qDebug() << "unknown project folder, no *.pro file found.";
    }
}

void CLudeCommandPackageInit::makeCludePackageJsonFile(const QString &package, const QString &name, const QString &path)
{
    QString message = QString("initilizing the project inside the package '%1' folder").arg(package);
    qDebug() << message.toLocal8Bit().constData();

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
        qDebug() << "Failed to initilize the project";
    }
}
