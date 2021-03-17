#ifndef PYTHON_H
#define PYTHON_H

#include "animal.h"
#include <QWidget>
#include <QPainter>

/**
  \
  \todo checkCollision to animal
*/
using namespace std;

class python : public animal
{
    // ALL_DOTS
private:
    static const int all_dots {900};
    QImage dot;
    QImage head;

public:

    python(QPoint pos);

    vector<QPoint> points;

    int dotss {3};


    void move(int height, int width, bool wall);

    int getAllDots(void);
    void draw(QPainter &qp);


};

#endif // PYTHON_H
