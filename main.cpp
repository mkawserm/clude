#include <QDebug>
#include <QCoreApplication>
#include "cludeobject.hpp"

#include "cludepackagedependency.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //clude parser
    CLudeObject clo;
    clo.process(a.arguments());
    return 0;
}

