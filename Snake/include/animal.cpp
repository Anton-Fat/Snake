#include "animal.h"

using namespace std;

animal::animal(QPoint pos)
{
    this->pos = pos;
}

int animal::getDotSize()
{
    return dot_size;
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
bool animal::checkCollision(int height, int width, const vector<QPoint> &points)
{
    for (int z = points.size()-1; z > 0; z--) {

        if ((z > 4) && (pos.x() == points.at(z).x()) && (pos.y() == points.at(z).y())) {
            return false;
        }
    }

    if ((pos.y() >= height)||(pos.y() < 0)||(pos.x() >= width)||(pos.x() < 0))
    {
        return false;
    }

    return true;
}
