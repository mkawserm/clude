#include "cludedependencyresolver.hpp"

CLudeDependencyResolver::CLudeDependencyResolver()
{

}

void CLudeDependencyResolver::setRootPackage(const QString &rp)
{
    this->mRootPackage = rp;
}

void CLudeDependencyResolver::resolve()
{
    if(this->mRootPackage.isEmpty()){
        qDebug() << "No root package defined";
        qDebug() << "set root package by callng setRootPackage(path)";
        return;
    }
    this->mResolvedDependency.clear();
    this->mVisited.clear();

    foreach (const QString &p, this->getDependencyList(this->mRootPackage)) {
        if(!this->mVisited.contains(p)) this->topSort(p);
    }
}

QStringStack CLudeDependencyResolver::getResolvedDependency() const
{
    return this->mResolvedDependency;
}

QStringList CLudeDependencyResolver::getDependencyList(const QString &path)
{
    CLudePackage vCLudePackage;
    vCLudePackage.fromJsonFile(path);
    QStringList lst;
    foreach (CLudePackageDependency t, vCLudePackage.dependency()) {
        lst.append(t.toString());
    }
    return lst;
}

QStringList CLudeDependencyResolver::getDependencyListFromString(const QString &str)
{
    CLudePackageDependency vCLudePackageDependency(str);
    QString path = QDir::toNativeSeparators(
                GConfig::repoPath()+
                "/"+vCLudePackageDependency.package().replace(".","/")+
                QLatin1Char('/')+vCLudePackageDependency.name()+
                QLatin1Char('/')+vCLudePackageDependency.version()+
                QLatin1Char('/')+vCLudePackageDependency.name()+".cde");
    return this->getDependencyList(path);
}

void CLudeDependencyResolver::topSort(const QString &pkg)
{
    this->mVisited.append(pkg);
    foreach (const QString &p, this->getDependencyListFromString(pkg)) {
        if(!this->mVisited.contains(p)) this->topSort(p);
    }
    this->mResolvedDependency.push(pkg);
}

