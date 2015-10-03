#ifndef PRIFILE_HPP
#define PRIFILE_HPP

#include <QString>
#include <QStringList>

class PriFile
{
    private:
        QString m_target;          // TARGET
        QString m_template;        // TEMPLATE

        QStringList m_qt;          // QT
        QStringList m_config;      // CONFIG

        QStringList m_sources;     // SOURCES
        QStringList m_headers;     // HEADERS
        QStringList m_forms;       // FORMS
        QStringList m_resources;   // RESOURCES
        QStringList m_distfiles;   // DISTFILES
        QStringList m_includepath; // INCLUDEPATH
        QStringList m_libs;        // LIBS
        QStringList m_include;     // INCLUDE

    public:
        PriFile();
};

#endif // PRIFILE_HPP
