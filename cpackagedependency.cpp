#include "cpackagedependency.hpp"

CPackageDependency::CPackageDependency()
{

}

QString CPackageDependency::package() const
{
    return this->m_package;
}


QString CPackageDependency::name() const
{
    return this->m_name;
}

QString CPackageDependency::optor() const
{
    return this->m_optor;
}

QString CPackageDependency::version() const
{
    return this->m_version;
}

void CPackageDependency::setPackage(const QString &a_package)
{
    this->m_package = a_package;
}

void CPackageDependency::setName(const QString &a_name)
{
    this->m_name = a_name;
}

void CPackageDependency::setOptor(const QString &a_optor)
{
    this->m_optor = a_optor;
}

void CPackageDependency::setVersion(const QString &a_version)
{
    this->m_version = a_version;
}

