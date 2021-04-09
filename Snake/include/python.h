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
    int dotss {3};

public:

    typedef struct pointsPathst {

        vector<QPoint> Path;
        vector<bool> pos;

    } pointsPathst;

    python(QPoint pos);
    ~python();

    vector<QPoint> pointsReal;

    pointsPathst pointsPath;


    void move(QSize size, bool wall, int dtime);

    int getAllDots(void);
    void draw(QPainter &qp);


};

#endif // PYTHON_H
