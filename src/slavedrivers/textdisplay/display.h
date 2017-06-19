#ifndef DISPLAY_H
#define DISPLAY_H

#include <QQuickPaintedItem>
#include <QPainter>
#include "segmentdisplay.h"

class Display : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)

public:
    Display();
    void paint(QPainter *painter);
    int columns();
    int rows();
    QString text();
    void setRows(int r);
    void setColumns(int c);
    Q_INVOKABLE void setContent(QByteArray content);

signals:
    void rowsChanged();
    void columnsChanged();


private:
    void updateList();

    QList<SegmentDisplay*> displays;
    int _rows;
    int _columns;
};

#endif // DISPLAY_H
