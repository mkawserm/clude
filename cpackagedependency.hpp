#ifndef CPACKAGEDEPENDENCY_HPP
#define CPACKAGEDEPENDENCY_HPP

#include <QString>
#include "cpackage.hpp"

class CPackage;
class CPackageDependency;

class CPackageDependency
{
    private:
        QString m_package;
        QString m_name;
        QString m_optor;
        QString m_version;
    public:
        CPackageDependency();
        QString package() const;
        QString name() const;
        QString optor() const;
        QString version() const;

        void setPackage(const QString &a_package);
        void setName(const QString &a_name);
        void setOptor(const QString &a_optor);
        void setVersion(const QString &a_version);
};

#endif // CPACKAGEDEPENDENCY_HPP
