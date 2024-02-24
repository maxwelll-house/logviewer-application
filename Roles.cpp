#include "Line.h"
#include "Model.h"
#include "Roles.h"

void RolesContainer::clear()
{
    m_roles.clear();
}

void RolesContainer::add(const RoleInfo& info) 
{
    m_roles.emplace_back(info);
}

RoleInfo RolesContainer::getById(const int id) const 
{
    for (const auto& elem : m_roles) 
    {
        if (elem.id == id) 
        {
            return elem;
        }
    }
    return {};
}

RoleInfo RolesContainer::getByRoleName(const QString& roleName) const 
{
    for (const auto& elem : m_roles) 
    {
        if (elem.roleName == roleName) 
        {
            return elem;
        }
    }
    return {};
}

RoleInfo RolesContainer::getByRoleTitle(const QString& title) const 
{
    for (const auto& elem : m_roles) 
    {
        if (elem.title == title) 
        {
            return elem;
        }
    }
    return {};
}

void RolesContainer::updateTitles(const QVariantMap& roleToTitleMap) 
{
    for (auto& elem : m_roles) {
        auto it = roleToTitleMap.find(elem.roleName);
        if (it != roleToTitleMap.end()) 
        {
            elem.title = it.value().toString();
        }
    }
}

QHash<int, QByteArray> RolesContainer::roleNames() const
{
    QHash<int, QByteArray> hash;
    for (const auto& elem : m_roles) 
    {
        hash.insert(elem.id, elem.roleName.toUtf8());
    }
    return hash;
}

QStringList RolesContainer::titles() const
{
    QStringList titles;
    for (const auto& elem : m_roles) 
    {
        titles << elem.title;
    }
    return titles;
}