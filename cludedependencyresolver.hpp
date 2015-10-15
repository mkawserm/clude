#ifndef CLUDEDEPENDENCYRESOLVER_HPP
#define CLUDEDEPENDENCYRESOLVER_HPP

#include <QMap>
#include <QDir>
#include <QStack>
#include <QDebug>
#include <QString>
#include <QDebug>
#include <QStringList>

#include "gconfig.hpp"
#include "cludepackage.hpp"
#include "cludepackagedependency.hpp"

typedef QStack<QString> QStringStack;

class CLudePackage;
class CLudeDependencyResolver;


class CLudeDependencyResolver
{
        QStringStack mResolvedDependency;
        QStringList mVisited;

        QString mRootPackage;
    public:
        CLudeDependencyResolver();
        void setRootPackage(const QString &rp);

        void resolve();
        QStringStack getResolvedDependency() const;

        QStringList getDependencyList(const QString &path);
        QStringList getDependencyListFromString(const QString &str);

    private:
        void topSort(const QString &pkg);

};

#endif // CLUDEDEPENDENCYRESOLVER_HPP
