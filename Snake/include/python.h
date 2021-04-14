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

    python(QPoint pos);
    ~python();


    typedef struct pointsPathst {

        vector<QPoint> Path;
        vector<bool> pos;

    } pointsPathst;


    vector<QPoint> pointsReal;

    pointsPathst pointsPath;


    void move(QSize size, bool wall, int dtime);

    int getAllDots(void);
    void addDot(const QPoint &point);
    void draw(QPainter &qp);


};

#endif // PYTHON_H
