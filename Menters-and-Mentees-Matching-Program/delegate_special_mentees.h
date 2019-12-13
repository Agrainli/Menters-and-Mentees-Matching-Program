#ifndef DELEGATE_SPECIAL_MENTEES_H
#define DELEGATE_SPECIAL_MENTEES_H

#include <QStyledItemDelegate>

class Delegate_Special_Mentees : public QStyledItemDelegate
{
    Q_OBJECT

public:
    Delegate_Special_Mentees(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // DELEGATE_SPECIAL_MENTEES_H
