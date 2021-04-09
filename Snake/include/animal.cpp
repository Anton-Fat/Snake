#include "animal.h"

/// \todo delete
#include <QDebug>

int animal::count = 0;

animal::animal(QPoint pos)
{
    this->pos = pos;

    animal::count++;
    qDebug() << "add animal +1";
}

animal::~animal()
{
    animal::count--;
    qDebug() << "del animal -1";
}

int animal::getDotSize()
{
    return dot_size;
}

//==============================================================================
int animal::getDistanse(float scale)
{
    return getDotSize()*scale;
}
//==============================================================================
bool animal::checkCollision(QSize size, const vector<QPoint> &points)
{
    for (int z = points.size()-1; z > 0; z--) {

        if ((z > 4) && (pos.x() == points.at(z).x()) && (pos.y() == points.at(z).y())) {
            return false;
        }
    }

    if ((pos.y() >= size.height())||(pos.y() < 0)||(pos.x() >= size.width())||(pos.x() < 0))
    {
        return false;
    }

    return true;
}
//==============================================================================
