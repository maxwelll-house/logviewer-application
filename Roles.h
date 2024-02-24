#pragma once

#include "Line.h"
#include "Model.h"

#include <QAbstractListModel>
#include <QList>

#include <vector>

struct RoleInfo
{
    int id;
    QString roleName;
    QString title;
};

class RolesContainer
{
    std::vector<RoleInfo>m_roles;
public:
    void clear();
    void add(const RoleInfo& info);

    RoleInfo getById(const int id) const;
    RoleInfo getByRoleName(const QString& roleName) const;
    RoleInfo getByRoleTitle(const QString& title) const;

    void updateTitles(const QVariantMap& roleToTitleMap);

    QHash<int, QByteArray> roleNames() const;
    QStringList titles() const;
};