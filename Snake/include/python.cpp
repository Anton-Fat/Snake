#include "python.h"
// 363
python::python(QPoint pos):animal(pos)
{

     // dots = 3;
    points.clear();

    for (int z = 0; z < dotss; z++) {
        points.push_back(QPoint(pos.x() - z * getDotSize(),
                                pos.y()));
    }

    dot.load(":/res/images/dot_10.png");
    head.load(":/res/images/head_10.png");


}

void python::move(int height, int width, bool wall)
{
    int x0, y0;
    points.insert(points.begin(), points.at(0));
    points.pop_back();

    if (angle == dir_left) {
        x0 = points.at(0).x() - getDotSize();
        if(!wall) {
            if (x0 < 0) x0 = width - getDotSize();
        }
        points.at(0).setX(x0);

    }

    if (angle == dir_right) {
        x0 = points.at(0).x() + getDotSize();
        if(!wall) {
            if (x0 >= width) x0 = 0;
        }
        points.at(0).setX(x0);
    }

    if (angle == dir_up) {
        y0 = points.at(0).y() - getDotSize();
        if(!wall) {
            if (y0 < 0) y0 = height - getDotSize();
        }
        points.at(0).setY(y0);
    }

    if (angle == dir_down) {
        y0 = points.at(0).y() + getDotSize();
        if(!wall) {
            if (y0 >= height) y0 = 0;
        }
        points.at(0).setY(y0);
    }
    pos = points.at(0);
}



int python::getAllDots()
{
    return all_dots;
}

void python::draw(QPainter &qp)
{
    for (int z = 0; z < points.size(); z++) {
        if (z == 0) {
            qp.drawImage(points.at(z).x(), points.at(z).y(), head);
        } else {
            qp.drawImage(points.at(z).x(), points.at(z).y(), dot);
        }
    }
}
