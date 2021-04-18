#include "python.h"
// 363

/// \todo delete
#include <QDebug>

python::python(QPoint pos):animal(pos)
{

     // dots = 3;
    pointsReal.clear();



    for (int z = 0; z < dotss; z++) {

        //addDot(QPoint(pos.x() - z * getDotSize(), pos.y()));
        addDot(QPoint(pos.x(), pos.y()));
    }

    dot.load(":/res/images/dot_10.png");
    head.load(":/res/images/head_10.png");


}
//==============================================================================
python::~python()
{

}
//==============================================================================
void python::addDot(const QPoint &point)
{
    pointsReal.push_back(point);
    pointsPath.Path.push_back(pointsReal.back());
    pointsPath.pos.push_back(true);
}
//==============================================================================
void python::move(QSize size, bool wall, int dtime)
{
    int x0, y0;

    QPoint delta;

    int i = 0;
    bool find = false, find_zero = false;

    while( (i < pointsReal.size()-1) &&  !find && !find_zero)
    {
        delta = pointsReal.at(i+1) - pointsReal.at(i);
        if (delta.isNull())
        {
            find_zero = true;
        }
        else if (delta.manhattanLength() < getDotSize())
        {
            find = true;
        }
        ++i;
    }

    pointsPath.Path.insert(pointsPath.Path.begin(), pointsPath.Path.at(0));

    if(find) {
        // insert point
        int j = 0;
        while (i != 0)
        {
            if(pointsPath.pos.at(j) == true)   i--;
            j++;
        }
        i = j;
        pointsPath.pos.insert(pointsPath.pos.begin()+i, false);

    } else {
        pointsPath.Path.pop_back();
    }

    qreal scaleLen = static_cast<qreal>(speed) * dtime / 10000;

    if (angleReal == dir_left) {
        x0 = pointsPath.Path.at(0).x() - getDistanse(scaleLen);
        if(!wall) {
            if (x0 < 0) x0 = size.width() - getDistanse(scaleLen);
        }
        pointsPath.Path.at(0).setX(x0);

    }

    if (angleReal == dir_right) {
        x0 = pointsPath.Path.at(0).x() + getDistanse(scaleLen);
        if(!wall) {
            if (x0 >= size.width()) x0 = 0;
        }
        pointsPath.Path.at(0).setX(x0);
    }

    if (angleReal == dir_up) {
        y0 = pointsPath.Path.at(0).y() - getDistanse(scaleLen);
        if(!wall) {
            if (y0 < 0) y0 = size.height() - getDistanse(scaleLen);
        }
        pointsPath.Path.at(0).setY(y0);
    }

    if (angleReal == dir_down) {
        y0 = pointsPath.Path.at(0).y() + getDistanse(scaleLen);
        if(!wall) {
            if (y0 >= size.height()) y0 = 0;
        }
        pointsPath.Path.at(0).setY(y0);
    }
    pos = pointsPath.Path.at(0);


    // only head
    for(int j = 0, i = 0; j < pointsPath.Path.size(); ++j)
    {
        if (pointsPath.pos.at(j) == true)
        {
         pointsReal.at(i) = pointsPath.Path.at(j);
         i++;
        }
    }

}
//==============================================================================
int python::getAllDots()
{
    return all_dots;
}
//==============================================================================
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
//==============================================================================
