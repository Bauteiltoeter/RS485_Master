#ifndef SEGMENTDISPLAY_H
#define SEGMENTDISPLAY_H

#include <QQuickPaintedItem>

class SegmentDisplay : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int character READ character WRITE setCharacter NOTIFY characterChanged)
public:
    SegmentDisplay();
    void paint(QPainter *painter);
    int character();
    void setCharacter(char c);

signals:
    void characterChanged();

private:
    int segments[16];

    uint8_t ascii_to_index(char ascii);
    void drawSegment(int segment, double scaling, QPainter* painter);
};

#endif // SEGMENTDISPLAY_H
