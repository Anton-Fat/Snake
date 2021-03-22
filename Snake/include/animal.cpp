#include "animal.h"

using namespace std;

int animal::count = 0;

animal::animal(QPoint pos)
{
    this->pos = pos;
}

int animal::getDotSize()
{
    return dot_size;
}

int animal::getDistanse(float scale)
{
    return getDotSize()*scale;
}

void animal::action_angle(int key)
{

    if ((key == Qt::Key_Left) && (angle != dir_right)) {
        angle = dir_left;
    }

    if ((key == Qt::Key_Right) && (angle != dir_left)) {
        angle = dir_right;
    }

    if ((key == Qt::Key_Up) && (angle != dir_down)) {
        angle = dir_up;
    }

    if ((key == Qt::Key_Down) && (angle != dir_up)) {
        angle = dir_down;
    }

}
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
