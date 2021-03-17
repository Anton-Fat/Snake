#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>

#define TIMER_LOOP

//==============================================================================

class python;

//==============================================================================


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
    QImage apple;

    QTimer *timer;


    bool Pause {false};

    python *m_python {nullptr};

    bool wall = false;

    static const int B_WIDTH = 300;
    static const int B_HEIGHT = 300;

    static const int RAND_POS = 29;
    static const int APPLE_SIZE = 10;

    int timerId;

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
