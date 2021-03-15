#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>

#define TIMER_LOOP



class Snake : public QWidget
{
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);
    ~Snake();

protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);

private:
    QImage dot;
    QImage head;
    QImage apple;

    QTimer *timer;

    enum Direction
    {
        dir_right = 0,
        dir_up = 90,
        dir_left = 180,
        dir_down = 270,
    };

    bool Pause {false};

    static const int B_WIDTH = 300;
    static const int B_HEIGHT = 300;
    static const int DOT_SIZE = 10;
    static const int ALL_DOTS = 900;
    static const int RAND_POS = 29;
    static const int DELAY = 200; //140;

    int timerId;
    int dots;
    int apple_x;
    int apple_y;

    int x[ALL_DOTS];
    int y[ALL_DOTS];

    Direction angle;

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
