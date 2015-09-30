#include <QDebug>
#include <QCoreApplication>
#include "cludecommandparser.hpp"

#include "cludepackagedependency.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /**********************************************************************************************
     * Start Parsing command line arguments
     * *******************************************************************************************/
    CLudeCommandParser ccp;
    ccp.process(a.arguments());
    return 0;
}

