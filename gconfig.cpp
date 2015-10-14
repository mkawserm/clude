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

