#ifndef MAP_H
#define MAP_H

#include <QWidget>

class Map
{
public:
    Map();
    Map(int width, int height);

    ~Map();

    QSize getSize(void);

    QSize getCountPoints(void);

    static const int grid {5};

protected:


private:


    int width = 300;
    int height = 300;


};

#endif // MAP_H
