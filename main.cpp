#include <QDebug>
#include <QCoreApplication>

#include "cludeobject.hpp"
#include "cludepackage.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CLudePackage p;
    p.setPackage("clude");
    p.setAuthor("kawser");
    p.setVersion("1.0.0");
    p.setBuild(0);
    p.addQdependency("core");
    p.addQdependency("gui");
    p.addQdependency("widgets");

    qDebug() << p.toJsonFile("package.json");

    //clude parser
    //CLudeObject clo;
    //clo.process(a.arguments());
    return 0;
}

