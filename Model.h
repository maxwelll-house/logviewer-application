#pragma once

#include "Line.h"
#include "Roles.h"

#include <QAbstractListModel>
#include <QList>

class Model: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList titles READ titles NOTIFY titlesChanged)
public:
    void reset(const QList<Line>& logs);
    void add(const Line& line);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        (void)parent;
        return m_lines.count();
    }

    QVariant data(const QModelIndex& index, int role) const override;
    Q_INVOKABLE void orderBy(const QString& columnName);
    QStringList titles() const;

    Q_INVOKABLE void updateTitles(const QVariantMap& roleToTitleMap);
    Q_INVOKABLE QString getTitle(const QString& roleName) const;
signals:
    void titlesChanged();
    void modelReloaded();
protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<Line> m_lines;
    RolesContainer m_rolesContainer;
};
