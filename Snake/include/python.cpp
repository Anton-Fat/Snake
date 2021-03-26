#include "python.h"
// 363

/// \todo delete
#include <QDebug>

python::python(QPoint pos):animal(pos)
{

     // dots = 3;
    pointsReal.clear();

    count++;

    for (int z = 0; z < dotss; z++) {
        pointsReal.push_back(QPoint(pos.x() - z * getDotSize(),
                                pos.y()));
    }

    dot.load(":/res/images/dot_10.png");
    head.load(":/res/images/head_10.png");


}

void python::move(QSize size, bool wall, int dtime)
{
    int x0, y0;

    QPoint delta;
    for(int i = 0; i < pointsReal.size()-1; ++i)
    {
        delta = pointsReal.at(i+1) - pointsReal.at(i);
        if (delta.manhattanLength() < getDotSize())
        {
            // insert point

        }

    }

    pointsReal.insert(pointsReal.begin(), pointsReal.at(0));
    pointsReal.pop_back();

    qreal scaleLen = static_cast<qreal>(speed) * dtime / 10000;

    //qDebug() << " dist " << QString::number(getDistanse(scaleLen));

    if (angle == dir_left) {
        x0 = pointsReal.at(0).x() - getDistanse(scaleLen);
        if(!wall) {
            if (x0 < 0) x0 = size.width() - getDistanse(scaleLen);
        }
        pointsReal.at(0).setX(x0);

    }

    if (angle == dir_right) {
        x0 = pointsReal.at(0).x() + getDistanse(scaleLen);
        if(!wall) {
            if (x0 >= size.width()) x0 = 0;
        }
        pointsReal.at(0).setX(x0);
    }

    if (angle == dir_up) {
        y0 = pointsReal.at(0).y() - getDistanse(scaleLen);
        if(!wall) {
            if (y0 < 0) y0 = size.height() - getDistanse(scaleLen);
        }
        pointsReal.at(0).setY(y0);
    }

    if (angle == dir_down) {
        y0 = pointsReal.at(0).y() + getDistanse(scaleLen);
        if(!wall) {
            if (y0 >= size.height()) y0 = 0;
        }
        pointsReal.at(0).setY(y0);
    }
    pos = pointsReal.at(0);
}



int python::getAllDots()
{
    return all_dots;
}

void python::draw(QPainter &qp)
{
    for (int z = 0; z < static_cast<int>(pointsReal.size()); z++) {
        if (z == 0) {
            qp.drawImage(pointsReal.at(z).x(), pointsReal.at(z).y(), head);
        } else {
            qp.drawImage(pointsReal.at(z).x(), pointsReal.at(z).y(), dot);
        }
    }
}
