#include "gconfig.hpp"

GConfig::GConfig()
{

}

QString GConfig::repoPath()
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
            if(ob.contains("LOCAL_REPOSITORY")){
                return ob.value("LOCAL_REPOSITORY").toString();
            }
        }
    }
    return QString();
}

QString GConfig::projectPriFilePath()
{
    QDir vDir(QDir::currentPath());
    vDir.setNameFilters(QStringList()<<"*.pro");
    QStringList one =  vDir.entryList(QDir::Files);
    if(one.size()==1){
        QString name = one[0].replace(".pro","");
        QString pri = QDir::toNativeSeparators(QDir::currentPath()+QDir::separator()+name+QLatin1String(".pri"));
        return pri;
    }
    else{
        return QString();
    }
}

QStringList GConfig::projectFileList()
{
    QString vPriFilePath = GConfig::projectPriFilePath();
    if(!vPriFilePath.isEmpty()){
        QFile vPriFile(vPriFilePath);
        if(vPriFile.open(QIODevice::ReadOnly))
        {
            QStringList vFileList;
            while(!vPriFile.atEnd())
            {
                QString vLine = QLatin1String(vPriFile.readLine().constData());
                if(vLine.indexOf("include")!=-1) continue;
                if(vLine.contains("="))
                {
                    vLine = vLine.split("=").at(1);
                }
                vLine = vLine.remove(QLatin1String("\\"))
                        .trimmed();
                //vLine = vLine.trimmed();
                //qDebug() << vLine.isEmpty();
                if(!vLine.isEmpty()) vFileList.append(vLine);
            }
            vPriFile.close();
            return vFileList;
        }
        else
        {
            qDebug() << "Can not open pri file";
        }
    }
    else{
        qDebug() << "No pri file found";
    }

    return QStringList();
}

void GConfig::copy(const QString &source, const QString &destination, quint8 &status)
{
        QString vSource = source;
        QString vDestination = destination;
        bool vExecuteCopy = true;

        //qDebug() << vSource;
        //qDebug() << vDestination;
        QFileInfo vSourceFileInfo(vSource);
        QFileInfo vDestinationFileInfo(vDestination);
        if(!vSourceFileInfo.isFile()){
            status = 0; //failed
            return;
        }

        if(!vDestinationFileInfo.dir().exists()){
            vDestinationFileInfo.dir().mkpath(vDestinationFileInfo.dir().absolutePath());
        }

        if(!QFile::exists(vDestination))
        {
            vExecuteCopy = true;
        }
        else{
            QString vSourceHash = GConfig::hash(vSource);
            QString vDestinationHash = GConfig::hash(vDestination);

            //qDebug() <<vSourceHash.toLocal8Bit().toHex();
            //qDebug() << vDestinationHash.toLocal8Bit().toHex();
            if(vSourceHash.isEmpty() || vDestinationHash.isEmpty())
            {
                vExecuteCopy = true;
            }
            else if(vSourceHash == vDestinationHash)
            {
                vExecuteCopy = false;
            }
        }// else overwrite is false


        if(vExecuteCopy)
        {
            if(QFile::copy(vSource,vDestination))
            {
                status = 1;//success
            }
            else
            {
                status = 0;//failed
            }
        }
        else
        {
            status = 3;//ignored
        }
}

QString GConfig::hash(const QString &source)
{
    QFile vSourceFile(source);
    QCryptographicHash vHash(QCryptographicHash::Sha3_512);

    if(vSourceFile.open(QIODevice::ReadOnly)){
        vHash.addData(&vSourceFile);
        return QLatin1String( vHash.result().constData() );
    }
    return QString();
}


