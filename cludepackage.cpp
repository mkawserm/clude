#include "cludePackage.hpp"

CLudePackage::CLudePackage()
{

}

QString CLudePackage::author() const
{
    return this->m_author;
}

QString CLudePackage::name() const
{
    return this->m_name;
}

QString CLudePackage::version() const
{
    return this->m_version;
}

qint64 CLudePackage::build() const
{
    return this->m_build;
}

QString CLudePackage::package() const
{
    return this->m_package;
}

QString CLudePackage::group() const
{
    return this->m_group;
}

QDateTime CLudePackage::created() const
{
    return this->m_created;
}

QDateTime CLudePackage::updated() const
{
    return this->m_updated;
}

QString CLudePackage::description() const
{
    return this->m_description;
}

QList<QString> CLudePackage::tags() const
{
    return this->m_tags;
}

QMap<QString, QString> CLudePackage::urls() const
{
    return this->m_urls;
}

QList<QString> CLudePackage::qdependency() const
{
    return this->m_qdependency;
}

QList<CLudePackageDependency> CLudePackage::dependency() const
{
    return this->m_dependency;
}

void CLudePackage::setAuthor(const QString &a_author)
{
    this->m_author = a_author;
}

void CLudePackage::setName(const QString &a_name)
{
    this->m_name = a_name;
}

void CLudePackage::setVersion(const QString &a_version)
{
    this->m_version = a_version;
}

void CLudePackage::setBuild(const qint64 &a_build)
{
    this->m_build = a_build;
}

void CLudePackage::setPackage(const QString &a_package)
{
    this->m_package = a_package;
}

void CLudePackage::setGroup(const QString &a_group)
{
    this->m_group = a_group;
}

void CLudePackage::setCreated(const QDateTime &a_created)
{
    this->m_created = a_created;
}

void CLudePackage::setUpdated(const QDateTime &a_updated)
{
    this->m_updated = a_updated;
}

void CLudePackage::setDescription(const QString &a_description)
{
    this->m_description = a_description;
}

void CLudePackage::addTag(const QString &tag)
{
    if(!this->m_tags.contains(tag)) this->m_tags.append(tag);
}

void CLudePackage::addUrl(const QString &name, const QString &val)
{
    this->m_urls.insert(name,val);
}

void CLudePackage::addQdependency(const QString &name)
{
    if(!this->m_qdependency.contains(name)) this->m_qdependency.append(name);
}

void CLudePackage::addDependency(const CLudePackageDependency &pdcy)
{
    this->m_dependency.append(pdcy);
}

QString CLudePackage::toJsonString()
{
    QJsonObject root;
    root["author"] = QJsonValue(this->m_author);
    root["name"] = QJsonValue(this->m_name);
    root["version"] = QJsonValue(this->m_version);
    root["build"] = QJsonValue(this->m_build);
    root["package"] = QJsonValue(this->m_package);

    root["group"] = QJsonValue(this->m_group);
    root["created"] = QJsonValue(this->m_created.toString("dd/MM/yyyy hh:mm:ss A"));
    root["updated"] = QJsonValue(this->m_updated.toString("dd/MM/yyyy hh:mm:ss A"));
    root["description"] = QJsonValue(this->m_description);


    QJsonArray vTags;
    foreach (const QString &tag, this->m_tags) {
        vTags.append(QJsonValue(tag));
    }
    root["tags"] = vTags;

    QJsonObject vUrls;
    foreach (const QString &key, this->m_urls.uniqueKeys()) {
        vUrls[key] = QJsonValue(this->m_urls.value(key));
    }
    root["urls"] = vUrls;

    QJsonArray vQdependency;
    foreach (const QString &dpdc, this->m_qdependency) {
        vQdependency.append(dpdc);
    }
    root["qdependency"] = vQdependency;

    QJsonArray vDependency;
    foreach (const CLudePackageDependency &dpdc , this->m_dependency) {
        QString vName = dpdc.package();
        vName.append(QLatin1String(".")+dpdc.name());
        vName.append(dpdc.optor());
        vName.append(dpdc.version());
        if(!vDependency.contains(vName)) vDependency.append(vName);
    }
    root["dependency"] = vDependency;
    QJsonDocument doc(root);
    return QLatin1String( doc.toJson(QJsonDocument::Indented).constData());
}

bool CLudePackage::toJsonFile(const QString &path)
{
    QFile vFile(path);
    if(vFile.open(QIODevice::ReadWrite|QIODevice::Text)){
        vFile.write(this->toJsonString().toLocal8Bit());
        vFile.close();
        return true;
    }
    else{
        return false;
    }
}

bool CLudePackage::fromJsonString(const QString &jstr)
{
    QJsonParseError *e = new QJsonParseError();
    QJsonDocument doc = QJsonDocument::fromJson(jstr.toLocal8Bit(),e);
    QJsonObject root = doc.object();

    this->m_author = root.value("author").toString();
    this->m_name = root.value("name").toString();
    this->m_version = root.value("version").toString();
    this->m_build = root.value("build").toVariant().toLongLong();
    this->m_package = root.value("package").toString();

    this->m_group = root.value("group").toString();
    this->m_created = QDateTime::fromString(root.value("created").toString(),QLatin1String("dd/MM/yyyy hh:mm:ss A"));
    this->m_updated = QDateTime::fromString(root.value("updated").toString(),QLatin1String("dd/MM/yyyy hh:mm:ss A"));
    this->m_description = root.value("description").toString();

    this->m_tags.clear();
    QJsonArray vTags = root.value("tags").toArray();
    foreach (const QJsonValue &val, vTags) {
        this->m_tags.append(val.toString());
    }

    this->m_urls.clear();
    QJsonObject vUrls = root.value("urls").toObject();
    foreach (const QString &key, vUrls.keys()) {
        this->m_urls[key] = vUrls[key].toString();
    }

    this->m_qdependency.clear();
    QJsonArray vQdependency = root.value("qdependency").toArray();
    foreach (const QJsonValue &val, vQdependency) {
        this->m_qdependency.append(val.toString());
    }

    this->m_dependency.clear();
    QJsonArray vDependency = root.value("dependency").toArray();
    foreach (const QJsonValue &val, vDependency) {
        this->m_dependency.append(CLudePackageDependency(val.toString()));
    }

    //qDebug() << e->errorString();
    return e->error==QJsonParseError::NoError;
}

bool CLudePackage::fromJsonFile(const QString &path)
{
    QFile vFile(path);
    if(vFile.open(QIODevice::ReadWrite|QIODevice::Text)){
        bool b = this->fromJsonString(QString(vFile.readAll().constData()));
        vFile.close();
        return b;
    }
    else{
        return false;
    }
}

