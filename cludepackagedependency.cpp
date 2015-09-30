#include "cludepackagedependency.hpp"

CLudePackageDependency::CLudePackageDependency()
{

}

CLudePackageDependency::CLudePackageDependency(const QString &p,const QString &n,const QString &o,const QString &v):
    m_package(p),
    m_name(n),
    m_optor(o),
    m_version(v)
{

}
QString CLudePackageDependency::package() const
{
    return this->m_package;
}


QString CLudePackageDependency::name() const
{
    return this->m_name;
}

QString CLudePackageDependency::optor() const
{
    return this->m_optor;
}

QString CLudePackageDependency::version() const
{
    return this->m_version;
}

void CLudePackageDependency::setPackage(const QString &a_package)
{
    this->m_package = a_package;
}

void CLudePackageDependency::setName(const QString &a_name)
{
    this->m_name = a_name;
}

void CLudePackageDependency::setOptor(const QString &a_optor)
{
    this->m_optor = a_optor;
}

void CLudePackageDependency::setVersion(const QString &a_version)
{
    this->m_version = a_version;
}

