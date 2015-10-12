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

    CLudeCommandPackage::process();
    //process all commands here
    if(this->isSet(save)){
        this->actionSave();
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

    QDir vDir(QDir::currentPath());
    vDir.setNameFilters(QStringList()<<"*.pro");
    QStringList one =  vDir.entryList(QDir::Files);
    if(one.size()==1){
        QString name = one[0].replace(".pro","");
        QString path = QDir::toNativeSeparators(QDir::currentPath()+QLatin1String("/")+name+QLatin1String(".cde"));
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
                this->copyRecursively(QDir::currentPath(),mProjectSaveLocation);
            }
        }
        else{
            qDebug() << "no clude package file found";
        }
    }
}

bool CLudeCommandPackageProject::copyRecursively(const QString &srcFilePath, const QString &tgtFilePath)
{
    QFileInfo srcFileInfo(srcFilePath);
    if (srcFileInfo.isDir()) {
        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
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
        //if(QFile::exists(tgtFilePath)) QFile::remove(tgtFilePath);
        if (!QFile::copy(srcFilePath,tgtFilePath)){
            qDebug() << "Failed to copy";
            return false;
        }
        else{
            return true;
        }
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

