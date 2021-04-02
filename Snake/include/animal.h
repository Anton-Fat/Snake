#ifndef ANIMAL_H
#define ANIMAL_H

#include <QWidget>
#include <QPoint>



using namespace std;

class animal
{

public:


    const string t_key_up {"key_up"};
    const string t_key_down {"key_down"};
    const string t_key_left {"key_left"};
    const string t_key_right {"key_right"};


    map <string, int> m_dict;

    static int count;

    animal(QPoint pos);

    int speed = 200; //140;

    QPoint pos;

    int getDotSize(void);
    int getDistanse(float scale);
    void action_angle(int key);
    bool checkCollision(QSize size, const std::vector<QPoint> &points);


protected:
    enum Direction
    {
        dir_right = 0,
        dir_up = 90,
        dir_left = 180,
        dir_down = 270,
    };

    Direction angle {dir_right};

private:


    int dot_size {10};
    int distanse {0};

};

#endif // ANIMAL_H
