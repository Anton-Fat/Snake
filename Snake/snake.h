#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>

#include <memory>

#include "include/map.h"
#include "player.h"

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



    int getFps() { return fps; }

protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);

private:

    static int fps;
    static const int max_count_python {4};

    int period = 1000 / fps;


    QImage apple;

    QTimer *timer;


    bool Pause {false};

    python *m_python_t[max_count_python]; // 444

    Player *m_player_2 {nullptr};

    std::vector<std::unique_ptr<Player>> m_players;

    bool wall = false;

    Map *m_map {nullptr};



    static const int APPLE_SIZE = 10;


    QPoint pos_apple;

    bool inGame;

    void loadImages();
    void initGame();
    void locateApple();
    void checkApple();
    void checkCollision();
    void move();
    void doDrawing();
    void gameOver(QPainter &);
    void outText(QPainter &qp, QString text);

private slots:
    void updateTime();

};
#endif // SNAKE_H
