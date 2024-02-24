#include "Line.h"
#include "Model.h"
#include "Roles.h"

#include <QAbstractListModel>
#include <QList>

void Model::reset(const QList<Line>& logs)
{
    if (logs.empty())
    {
        return;
    }
    m_lines.clear();
    m_rolesContainer.clear();

    int rolesCount = logs.at(0).m_line.size();

    for (int i = 1; i <= rolesCount; i++) 
    {
        int roleId = Qt::UserRole + i;
        QString roleName = "Column #" + QString::number(i);

        m_rolesContainer.add({ roleId, roleName, roleName });
    }

    beginResetModel();
    m_lines = logs;
    endResetModel();

    emit modelReloaded();
}
void Model::add(const Line& line)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_lines << line;
    endInsertRows();
}

QVariant Model::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() > m_lines.count())
    {
        return QVariant();
    }

    const Line& line = m_lines[index.row()];
    int idx = role % (Qt::UserRole + 1);
    if (idx < line.m_line.size())
    {
        return line.m_line[idx];
    }
    return {};
}

Q_INVOKABLE void Model::orderBy(const QString& columnName) 
{
    RoleInfo info = m_rolesContainer.getByRoleTitle(columnName);
    int idx = info.id % (Qt::UserRole + 1);

    std::sort(m_lines.begin(), m_lines.end(),
        [idx](const Line& lhs, const Line& rhs) { return lhs.m_line[idx] < rhs.m_line[idx]; });

    dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, 0));

}

QStringList Model::titles() const
{
    return m_rolesContainer.titles();
}

Q_INVOKABLE void Model::updateTitles(const QVariantMap& roleToTitleMap)
{
    m_rolesContainer.updateTitles(roleToTitleMap);
    emit titlesChanged();
}

Q_INVOKABLE QString Model::getTitle(const QString& roleName) const
{
    return m_rolesContainer.getByRoleName(roleName).title;
}

QHash<int, QByteArray> Model::roleNames() const
{
    return m_rolesContainer.roleNames();
}
