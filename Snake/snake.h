#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>

#include <memory>

#include "include/map.h"
#include "player.h"

#include <algorithm>
#include <random>


#define TIMER_LOOP

//==============================================================================

class python;

//==============================================================================

using namespace std;

class Snake : public QWidget
{
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);
    ~Snake();


    using Ptr = std::unique_ptr<Player>;

    std::vector<Ptr>::iterator getObject(string const& objName);


    const map <string, int> control_1 {{Player::t_key_up, Qt::Key_Up},
                                 {Player::t_key_down, Qt::Key_Down},
                                 {Player::t_key_left, Qt::Key_Left},
                                 {Player::t_key_right, Qt::Key_Right}};
    const map <string, int> control_2 {{Player::t_key_up, Qt::Key_W},
                                 {Player::t_key_down, Qt::Key_S},
                                 {Player::t_key_left, Qt::Key_A},
                                 {Player::t_key_right, Qt::Key_D}};


    int getFps() { return fps; }

    void debugShowCntObject(void);

protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);

private:

    static int fps;
    //static const int max_count_python {4};
    //static const int max_count_player {100};

    int period = 1000 / fps;
    std::mt19937 gen;


    QImage apple;

    QTimer *timer;


    bool Pause {false};

    // python *m_python_t[max_count_python]; // 444

    std::vector<std::unique_ptr<python>> m_pythons;

//    Player *m_player_t[max_count_player];

    std::vector<std::unique_ptr<Player>> m_players;



    bool wall = false;

    Map *m_map {nullptr};



    static const int APPLE_SIZE = 10;


    QPoint pos_apple;

    bool inGame;
    uint genValue(int & val, const int &N);

    void loadImages();
    void initGame();
    void locateApple();
    void checkApple();
    void checkCollision();
    void move();
    void doDrawing();
    void gameOver(QPainter &);
    void outText(QPainter &qp, QString text);


    void eraseObject(QString text);
    void resetAll(void);

private slots:
    void updateTime();

};
#endif // SNAKE_H
