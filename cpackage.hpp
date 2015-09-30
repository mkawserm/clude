/**************************************************************************************************
 * Class Name     : CPackage
 * Base Class     :
 * Class Version  : 1.0.0
 * SourceCodeURL  :
 * Date           : 27/08/2015
 * Time           : 04:25 PM
 *
 * Author         : kawser
 * AuthorGit      : https://www.github.com/mkawserm
 * AuthorWeb      : https://kawser.org
 *
 * Objective      :
 * Description    : Clude Package - contains full package information
 *
 * VersionScheme  : major.stage.revision
 *                  major    -> major changes of the interface
 *                  stage    -> 0=alpha,1=beta,2=rc1,3=rc2,4=rc3,5=final
 *                  revision -> means bug fixed
 * BuildScheme    : auto incremented number
 *************************************************************************************************/

#ifndef CPACKAGE_HPP
#define CPACKAGE_HPP


#include <QList>
#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "cpackagedependency.hpp"

class CPackage;
class CPackageDependency;

class CPackage
{
    private:
        QString m_author;
        QString m_name;
        QString m_version; // major.stage.revision
        QString m_build;   // auto incremented number
        QString m_package;

        QString m_group;
        QDateTime m_created;
        QDateTime m_updated;
        QString m_description;

        QMap <QString,QString> m_urls;
        QList <QString> m_qdependency;
        QList <CPackageDependency> m_dependency;

    public:
        CPackage();
        QString author() const;
        QString package() const;
        QString name() const;
        QString version() const;
        QString build() const;
        QList<CPackageDependency> dependency() const;
        QList<QString> qdependency() const;

        QString toJsonString();
        bool fromJsonString(const QString &jstr);
};

#endif // CPACKAGE_HPP
