#include "cludecommandpackageproject.hpp"

CLudeCommandPackageProject::CLudeCommandPackageProject()
{
    this->addDescription(QLatin1String("initilize project, install project, resolve dependency"));

}

void CLudeCommandPackageProject::process()
{
    QCommandLineOption save(
                QStringList()<<"save",
                QCoreApplication::translate("main", "save the project to local repository")
                );
    this->addOption(save);

    QCommandLineOption resolve(
                QStringList()<<"resolve",
                QCoreApplication::translate("main","resolve dependency")
                );
    this->addOption(resolve);

    QCommandLineOption list_files(
                QStringList()<<"list-files",
                QCoreApplication::translate("main", "show the files list")
                );
    this->addOption(list_files);

    CLudeCommandPackage::process();
    //process all commands here
    if(this->isSet(save)){
        this->actionSave();
    }
    else if(this->isSet(resolve)){
        this->actionResolve();
    }
    else if(this->isSet(list_files)){
        this->actionListFiles();
    }
    else{
        qDebug() <<"do not know, what to do? see help";
    }
}

QString CLudeCommandPackageProject::name()
{
    return QLatin1String("project");
}

QString CLudeCommandPackageProject::version()
{
    return QLatin1String("1.0.0");
}

void CLudeCommandPackageProject::actionSave()
{
    qDebug() << "Saving the project to local repo...";

    //get local repository folder location
    QString mLocalRepoPath = this->getConfigJson(QLatin1String("LOCAL_REPOSITORY"));
    if(mLocalRepoPath.isEmpty()){
        qDebug() << "LOCAL_REPOSITORY is not defined on the config file";
        return;
    }

        QString path = GConfig::projectPriFilePath().replace(".pri",".cde");
        if(QFile::exists(path)){
            CLudePackage vPackage;
            if(vPackage.fromJsonFile(path)){
                QString mProjectSaveLocation = QDir::toNativeSeparators(
                            mLocalRepoPath+
                            QLatin1Char('/')+
                            vPackage.package().replace(QLatin1Char('.'),QLatin1Char('/'))+
                            QLatin1Char('/')+vPackage.name()+QLatin1Char('/')+
                            vPackage.version()
                            );
                qDebug() <<":: LOCATION : "<<mProjectSaveLocation<<" ::";
                //this->copyRecursively(QDir::currentPath(),mProjectSaveLocation);
                QStringList vFiles = GConfig::projectFileList();
                while(!vFiles.isEmpty())
                {
                    const QString vFilePath = vFiles.takeFirst();
                    //qDebug() << vFilePath;
                    QString source = QDir::toNativeSeparators(
                                QString(vFilePath).replace(QLatin1String("$$PWD"),QDir::currentPath())
                                );
                    QString destination = QDir::toNativeSeparators(
                                QString(vFilePath).replace(QLatin1String("$$PWD"),mProjectSaveLocation)
                                );

                    quint8 status;
                    QByteArray msg;
                    msg.append(source);
                    msg.append(" --> ");
                    msg.append(destination);
                    GConfig::copy(source,destination,status);
                    if(status==0){
                        msg.prepend("FAILED :: ");
                    }
                    else if(status==1){
                        msg.prepend("COPIED :: ");
                    }
                    else if(status==3){
                        msg.prepend("IGNORED :: ");
                    }

                    qDebug() << msg.constData();
                }
            }
        }
        else{
            qDebug() << "no clude package configuration file found";
        }
}

void CLudeCommandPackageProject::actionResolve()
{
    //TODO resolve all dependency including children packages
    qDebug() << "resolving dependency...";
    QString vPackageFilePath = this->getCLudePackageFilePath();
    QString vProjectPath = QDir::currentPath();
    if(!vPackageFilePath.isEmpty()){
        if(!GConfig::repoPath().isEmpty()){
            CLudeDependencyResolver cdr;
            cdr.setRootPackage(vPackageFilePath);
            cdr.resolve();
            QStringStack dpdc= cdr.getResolvedDependency();
            QStringList vPriFilePathList;
            while(!dpdc.isEmpty()){
                QString pname = dpdc.pop();
                qDebug() << "PACKAGE: "<<pname.toLocal8Bit().constData();
                CLudePackageDependency clpd(pname);
                QString vTgtSource = QDir::toNativeSeparators(GConfig::repoPath()+QLatin1Char('/')+
                                                              clpd.package().replace(".","/")+
                                                              QLatin1Char('/')+clpd.name()+
                                                              QLatin1Char('/')+clpd.version());
                QString vTgtLocation = QDir::toNativeSeparators(vProjectPath+QLatin1Char('/')+
                                                                clpd.package().replace(".","/")+
                                                                QLatin1Char('/')+clpd.name());
                vPriFilePathList.append(clpd.package().replace(".","/")+
                                        QLatin1Char('/')+
                                        clpd.name()+
                                        QLatin1Char('/')+
                                        clpd.name()+
                                        QLatin1String( ".pri")
                                        );

                this->copyRecursively(vTgtSource,vTgtLocation);
            }

            //Now include all pri files to the current project
            qDebug() << "\n\n\n::INCLUDING PACKAGES  TO THE PROJECT::";
            QString vPriPath = GConfig::projectPriFilePath();
            //if(QFile::exists(vPriPath)){
                QFile vPriFile(vPriPath);
                if(vPriFile.open(QIODevice::ReadWrite|QIODevice::Text)){
                    QByteArray data = vPriFile.readAll();
                    vPriFile.seek(vPriFile.size());
                    while(!vPriFilePathList.isEmpty()){
                        QString p = vPriFilePathList.takeFirst();
                        QString inc = QString("\ninclude(%1)\n").arg(p);
                        if(data.indexOf(inc)==-1){
                            vPriFile.write(inc.toLocal8Bit());
                            qDebug() <<"  "<< p.toLocal8Bit().constData();
                        }
                    }
                    vPriFile.close();
                }
            //}

        }
        else{
            qDebug() << "No local repository path found";
        }
    }
    else{
        qDebug() << "no clude package configuration file found";
    }

}

void CLudeCommandPackageProject::actionListFiles()
{
    QStringList files = GConfig::projectFileList();
    //this->walk(QDir::currentPath(),files,QStringList()<<".git"<<".gitignore");
    qDebug() << "FILES LIST:";
    foreach (const QString &file, files) {
        qDebug() << file.toLocal8Bit().constData();
    }
}

bool CLudeCommandPackageProject::copyRecursively(const QString &srcFilePath, const QString &tgtFilePath)
{
    QFileInfo srcFileInfo(srcFilePath);
    if (srcFileInfo.isDir()) {
        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::NoDot | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        foreach (const QString &fileName, fileNames) {
            //qDebug() << fileName;
            //lets exlude the files and folder we don't want to add to the repository
            if(fileName == ".git") continue;
            else if(fileName == ".gitignore") continue;
            else if(fileName.toLower() == "main.cpp") continue;
            else if(fileName.endsWith(".pro")) continue;
            else if(fileName.endsWith(".user")) continue;

            const QString newSrcFilePath
                    = QDir::toNativeSeparators(srcFilePath + QLatin1Char('/') + fileName);
            const QString newTgtFilePath
                    = QDir::toNativeSeparators(tgtFilePath + QLatin1Char('/') + fileName);
            //if (!this->copyRecursively(newSrcFilePath, newTgtFilePath)) return false;
            //qDebug() <<newSrcFilePath;
            //qDebug() <<newTgtFilePath;
            this->copyRecursively(newSrcFilePath,newTgtFilePath);
        }
    } else {


        QFileInfo targetDir(tgtFilePath);
        if(!targetDir.dir().exists()){
            targetDir.dir().mkpath(targetDir.dir().absolutePath());
        }
        qDebug() << "copying: "
                 << QDir::toNativeSeparators(srcFilePath)
                 << "->"
                 << QDir::toNativeSeparators(tgtFilePath);
        if(QFile::exists(tgtFilePath)) QFile::remove(tgtFilePath);
        if (!QFile::copy(srcFilePath,tgtFilePath)){
            qDebug() << "Failed to copy";
            return false;
        }
        else{
            return true;
        }

        /*
        if(!targetDir.exists()){
            qDebug() << "copying: "
                     << QDir::toNativeSeparators(srcFilePath)
                     << "->"
                     << QDir::toNativeSeparators(tgtFilePath);

            if (!QFile::copy(srcFilePath,tgtFilePath)){
                qDebug() << "Failed to copy";
                return false;
            }
            else{
                return true;
            }
        }
        else{
            if(targetDir.size()!=srcFileInfo.size()){
                qDebug() << "copying: "
                         << QDir::toNativeSeparators(srcFilePath)
                         << "->"
                         << QDir::toNativeSeparators(tgtFilePath);
                if(QFile::exists(tgtFilePath)) QFile::remove(tgtFilePath);
                if (!QFile::copy(srcFilePath,tgtFilePath)){
                    qDebug() << "Failed to copy";
                    return false;
                }
                else{
                    return true;
                }
            }
            else{
                qDebug() << "Source file and target file already updated";
                return true;
            }
        }*/
    }
    return true;
}

QString CLudeCommandPackageProject::getConfigJson(const QString &key)
{
    QString path = QCoreApplication::applicationFilePath();
    if (path.endsWith(".exe")){
        path = path.replace(".exe",".json");
    }
    if(!QFile::exists(path)) return QString();
    QFile mCF(path);
    if(mCF.open(QIODevice::ReadOnly)){
        QJsonDocument jd = QJsonDocument::fromJson(mCF.readAll());
        if(jd.isObject()){
            QJsonObject ob = jd.object();
            if(ob.contains(key)){
                return ob.value(key).toString();
            }
        }
    }
    return QString();
}

void CLudeCommandPackageProject::walk(const QString &path, QStringList &files,const QStringList &exclude)
{
    QFileInfo vPath(path);
    if(vPath.isDir()){
        QDir sourceDir(path);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        foreach (const QString &fileName, fileNames) {
            if(exclude.contains(fileName)) continue;
            const QString vNewPath = QDir::toNativeSeparators(path + QLatin1Char('/') + fileName);
            this->walk(vNewPath,files,exclude);
        }
    }
    else{
        files.append(path);
    }
}

QString CLudeCommandPackageProject::getCLudePackageFilePath()
{
    QDir vDir(QDir::currentPath());
    vDir.setNameFilters(QStringList()<<"*.pro");
    QStringList one =  vDir.entryList(QDir::Files);
    if(one.size()==1){
        QString name = one[0].replace(".pro","");
        QString path = QDir::toNativeSeparators(QDir::currentPath()+QLatin1String("/")+name+QLatin1String(".cde"));

        return path;
    }
    return QString();
}

