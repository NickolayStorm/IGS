#ifndef DRAWING_H
#define DRAWING_H
#include <QPainter>
#include <QPoint>

class Drawing
{
private:

//    static Drawing *_self;
public:
    enum ColorOption : int {WhitePalette = 1, BlackPalette = 2};
    Drawing();
//    static Drawing* instance();
    void drawPoint(QPainter&, QPoint&);
    void drawAxe(QPainter&, QPoint &begin, QPoint &end, QString name);
    void setColorParams(QPainter&, ColorOption opts);

};

#endif // DRAWING_H
