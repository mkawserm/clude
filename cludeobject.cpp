#include "cludeobject.hpp"

CLudeObject::CLudeObject()
{
    QCoreApplication::setApplicationName("clude");
    QCoreApplication::setApplicationVersion("1.0.0");

    this->m_parser.setApplicationDescription("clude is a c++ package manager");
    this->m_parser.addHelpOption();
    this->m_parser.addVersionOption();
}

void CLudeObject::process(const QStringList &argl)
{
    //add all options here

    //present working directory
    QCommandLineOption pwd(QStringList()<<"pwd",QCoreApplication::translate("main","show present working directoy"));
    this->m_parser.addOption(pwd);

    // initilize the project and create package.json file
    QCommandLineOption init_project(
                QStringList() << "init",
                QCoreApplication::translate("main", "initilize project inside the <package> folder"),
                QCoreApplication::translate("main", "package"));
    this->m_parser.addOption(init_project);


    this->m_parser.process(argl);
    if(this->m_parser.isSet(pwd)){
        std::cout<<QDir::currentPath().toLocal8Bit().constData();
    }
    else if(this->m_parser.isSet(init_project)){
        QString package = this->m_parser.value(init_project);
        CLudeObject::initilizeProject(package);
    }
}

void CLudeObject::initilizeProject(const QString &package)
{
    QString message = QString("initilizing the project inside the package '%1' folder").arg(package);
    qDebug() << message;
}

