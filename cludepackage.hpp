/**************************************************************************************************
 * Class Name     : CLudePackage
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

#ifndef CLUDEPACKAGE_HPP
#define CLUDEPACKAGE_HPP


#include <QFile>
#include <QList>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "cludePackagedependency.hpp"

class CLudePackage;
class CLudePackageDependency;

class CLudePackage
{
    private:
        QString m_author;
        QString m_name;
        QString m_version; // major.stage.revision
        qint64 m_build;    // auto incremented number
        QString m_package;

        QString m_group;
        QDateTime m_created;
        QDateTime m_updated;
        QString m_description;

        QList <QString> m_tags;
        QList <QString> m_licenses;
        QMap <QString,QString> m_urls;             // author,documentation,download every field
                                                   // can have multiple links seperated by ";"
        QList <QString> m_qdependency;
        QList <CLudePackageDependency> m_dependency;

    public:
        CLudePackage();

        QString author() const;
        QString name() const;
        QString version() const;
        qint64 build() const;
        QString package() const;

        QString group() const;
        QDateTime created() const;
        QDateTime updated() const;
        QString description() const;

        QList<QString> licenses() const;
        QList<QString> tags() const;
        QMap<QString,QString> urls() const;
        QList<QString> qdependency() const;
        QList<CLudePackageDependency> dependency() const;

        void setAuthor(const QString &a_author);
        void setName(const QString &a_name);
        void setVersion(const QString &a_version);
        void setBuild(const qint64 &a_build);
        void setPackage(const QString &a_package);

        void setGroup(const QString &a_group);
        void setCreated(const QDateTime &a_created);
        void setUpdated(const QDateTime &a_updated);
        void setDescription(const QString &a_description);

        void addLicense(const QString &name);
        void addTag(const QString &tag);
        void addUrl(const QString &name, const QString &val);
        void addQdependency(const QString &name);
        void addDependency(const CLudePackageDependency &pdcy);

        QString toJsonString();
        bool toJsonFile(const QString &path);

        bool fromJsonString(const QString &jstr);
        bool fromJsonFile(const QString &path);
};

#endif // CLUDEPACKAGE_HPP
