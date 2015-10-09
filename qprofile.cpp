#include "qprofile.hpp"

QProFile::QProFile()
{

}

QProFile::QProFile(const QString &path)
{
    this->setPath(path);
}

void QProFile::setPath(const QString &path)
{
    this->m_path = path;
}

QString QProFile::path() const
{
    return this->m_path;
}

QString QProFile::lastError() const
{
    return this->m_last_error;
}

bool QProFile::isValid() const
{
    return !this->m_path.isEmpty();
}

bool QProFile::parse()
{
    //reset the variables
    this->m_target.clear();
    this->m_template.clear();

    this->m_qt.clear();
    this->m_config.clear();

    this->m_sources.clear();
    this->m_headers.clear();
    this->m_resources.clear();
    this->m_distfiles.clear();
    this->m_include.clear();

    //Now start parsing

    return false;
}

