#ifndef CLUDEPACKAGEDEPENDENCY_HPP
#define CLUDEPACKAGEDEPENDENCY_HPP

#include <QString>
#include "cludepackage.hpp"

class CLudePackage;
class CLudePackageDependency;

class CLudePackageDependency
{
    private:
        QString m_package;
        QString m_name;
        QString m_optor;
        QString m_version;
    public:
        CLudePackageDependency();
        CLudePackageDependency(const QString &p,const QString &n,const QString &o,const QString &v);
        QString package() const;
        QString name() const;
        QString optor() const;
        QString version() const;

        void setPackage(const QString &a_package);
        void setName(const QString &a_name);
        void setOptor(const QString &a_optor);
        void setVersion(const QString &a_version);
};

#endif // CLUDEPACKAGEDEPENDENCY_HPP
