#include "cludeobject.hpp"

CLudeObject::CLudeObject()
{
    QCoreApplication::setApplicationName("clude");
    QCoreApplication::setApplicationVersion("1.0.0");

    this->m_parser.setApplicationDescription("clude c++ source package manager");
    this->m_parser.addHelpOption();
    this->m_parser.addVersionOption();
}

void CLudeObject::process(const QStringList &argl)
{
    //add all options here

    //present working directory
    QCommandLineOption pwd(QStringList()<<"pwd",QCoreApplication::translate("main","show present working directoy"));
    this->m_parser.addOption(pwd);

    // initilize the project and create package.json file
    QCommandLineOption init_project(
                QStringList() << "init",
                QCoreApplication::translate("main", "initilize project inside the <package> folder"),
                QCoreApplication::translate("main", "package"));
    this->m_parser.addOption(init_project);

    //update build
    QCommandLineOption update_build(
                QStringList()<<"update-build",
                QCoreApplication::translate("main","update build number of the given path"),
                QCoreApplication::translate("main","path"));
    this->m_parser.addOption(update_build);


    this->m_parser.process(argl);
    if(this->m_parser.isSet(pwd)){
        std::cout<<QDir::currentPath().toLocal8Bit().constData();
    }
    else if(this->m_parser.isSet(init_project)){
        QDir vDir(QDir::currentPath());
        vDir.setNameFilters(QStringList()<<"*.pro");
        QStringList one =  vDir.entryList(QDir::Files);
        if(one.size()==1){
            QString package = this->m_parser.value(init_project);
            QString path = QDir::toNativeSeparators(QDir::currentPath()+QLatin1String("/cludepackage.json"));
            QString pro = QDir::toNativeSeparators(QDir::currentPath()+QLatin1String("/")+one[0]);
            QString name = one[0].replace(".pro","");
            QString pri = QDir::toNativeSeparators(QDir::currentPath()+QLatin1String("/")+name+QLatin1String(".pri"));
            CLudeObject::initilizeProject(package,name,path);
            QFile vPriFile(pri);
            if(!vPriFile.exists()){
                if(vPriFile.open(QIODevice::WriteOnly|QIODevice::Text)){
                    vPriFile.write("SOURCES += \\\n");
                    vPriFile.write("\n");
                    vPriFile.write("HEADERS += \\\n");

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

    }//end of init command
    else if(this->m_parser.isSet(update_build)){
        QString path = this->m_parser.value(update_build);
        CLudeObject::updateBuild(path);
    }//end of update build command
}

void CLudeObject::initilizeProject(const QString &package, const QString &name, const QString &path)
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

void CLudeObject::updateBuild(const QString &path)
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
