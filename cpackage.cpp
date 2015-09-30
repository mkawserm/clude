#include "cpackage.hpp"

CPackage::CPackage()
{

}

QString CPackage::author() const
{
    return this->m_author;
}

QString CPackage::name() const
{
    return this->m_name;
}

QString CPackage::version() const
{
    return this->m_version;
}

quint64 CPackage::build() const
{
    return this->m_build;
}

QString CPackage::package() const
{
    return this->m_package;
}

QString CPackage::group() const
{
    return this->m_group;
}

QDateTime CPackage::created() const
{
    return this->m_created;
}

QDateTime CPackage::updated() const
{
    return this->m_updated;
}

QString CPackage::description() const
{
    return this->m_description;
}

QMap<QString, QString> CPackage::urls() const
{
    return this->m_urls;
}

QList<QString> CPackage::qdependency() const
{
    return this->m_qdependency;
}

QList<CPackageDependency> CPackage::dependency() const
{
    return this->m_dependency;
}

void CPackage::setAuthor(const QString &a_author)
{
    this->m_author = a_author;
}

void CPackage::setName(const QString &a_name)
{
    this->m_name = a_name;
}

void CPackage::setVersion(const QString &a_version)
{
    this->m_version = a_version;
}

void CPackage::setBuild(const quint64 &a_build)
{
    this->m_build = a_build;
}

void CPackage::setPackage(const QString &a_package)
{
    this->m_package = a_package;
}

void CPackage::setGroup(const QString &a_group)
{
    this->m_group = a_group;
}

void CPackage::setCreated(const QDateTime &a_created)
{
    this->m_created = a_created;
}

void CPackage::setUpdated(const QDateTime &a_updated)
{
    this->m_updated = a_updated;
}

void CPackage::setDescription(const QString &a_description)
{
    this->m_description = a_description;
}

void CPackage::addUrl(const QString &name, const QString &val)
{
    this->m_urls.insert(name,val);
}

void CPackage::addQdependency(const QString &name)
{
    if(!this->m_qdependency.contains(name)) this->m_qdependency.append(name);
}

void CPackage::addDependency(const CPackageDependency &pdcy)
{
    this->m_dependency.append(pdcy);
}

