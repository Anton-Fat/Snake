#ifndef ANIMAL_H
#define ANIMAL_H

#include <QWidget>
#include <QPoint>



using namespace std;

class animal
{

public:

    animal(QPoint pos);
    ~animal();


    enum Direction
    {
        dir_right = 0,
        dir_up = 90,
        dir_left = 180,
        dir_down = 270,
    };

    static int count;


    int speed = 200; //140;

    QPoint pos;

    int getDotSize(void);
    int getDistanse(float scale);
    bool checkCollision(QSize size, const std::vector<QPoint> &points);

    Direction angle {dir_right};

//protected:


    //Direction angle {dir_right};

private:



    int dot_size {10};
    int distanse {0};

};

#endif // ANIMAL_H
