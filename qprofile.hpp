/**************************************************************************************************
 * Class Name     :
 * Base Class     : QObject
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
 * Description    :
 *************************************************************************************************/

#ifndef QPROFILE_HPP
#define QPROFILE_HPP

#include <QDebug>
#include <QString>
#include <QStringList>

class QProFile
{
    private:
        QString m_path;
        QString m_last_error;

        QString m_target;
        QString m_template;

        QStringList m_qt;
        QStringList m_config;

        QStringList m_sources;
        QStringList m_headers;
        QStringList m_resources;
        QStringList m_distfiles;
        QStringList m_include;

    public:
        explicit QProFile();
        explicit QProFile(const QString &path);


        void setPath(const QString &path);
        QString path() const;

        QString lastError() const;

        bool isValid() const;

        bool parse();
};

#endif // QPROFILE_HPP
