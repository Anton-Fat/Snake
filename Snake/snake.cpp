#include <QPainter>
#include <QTime>

#include <QTimer>

#include "snake.h"

Snake::Snake(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet({"background-color:rgb(0, 30, 10);"

                  });
    angle = dir_right;
    inGame = true;

    resize(B_WIDTH, B_HEIGHT);
    loadImages();
    initGame();
}

Snake::~Snake()
{
    delete timer;
}

void Snake::loadImages() {

    dot.load(":/res/images/dot_10.png");
    head.load(":/res/images/head_10.png");
    apple.load(":/res/images/apple_10.png");
}

void Snake::initGame() {

    dots = 3;

    for (int z = 0; z < dots; z++) {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }

    locateApple();

    #ifdef TIMER_LOOP
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(DELAY);
    #else
    timerId = startTimer(DELAY);
    #endif

}

void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    doDrawing();
}

void Snake::doDrawing() {

    QPainter qp(this);

    if (inGame) {

        qp.drawImage(apple_x, apple_y, apple);

        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }

        if (Pause) {
            outText(qp, "Pause");

        }

    } else {

        gameOver(qp);
    }
}

void Snake::gameOver(QPainter &qp) {   
    outText(qp, "Game over");
}

void Snake::outText(QPainter &qp, QString text)
{
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(text);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, text);
}

void Snake::updateTime()
{
    if(!Pause){
        if (inGame) {

            checkApple();
            checkCollision();
            move();
        }


    }
    repaint();

}

void Snake::checkApple() {

    if ((x[0] == apple_x) && (y[0] == apple_y)) {

        dots++;
        locateApple();
    }
}

void Snake::move() {

    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (angle == dir_left) {
        x[0] -= DOT_SIZE;
    }

    if (angle == dir_right) {
        x[0] += DOT_SIZE;
    }

    if (angle == dir_up) {
        y[0] -= DOT_SIZE;
    }

    if (angle == dir_down) {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision() {

    for (int z = dots; z > 0; z--) {

        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }

    if ((y[0] >= B_HEIGHT)||(y[0] < 0)||(x[0] >= B_WIDTH)||(x[0] < 0))
    {
        inGame = false;
    }

    if(!inGame) {
        killTimer(timerId);
    }
}

void Snake::locateApple() {

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;
    apple_x = (r * DOT_SIZE);

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);
    #ifndef TIMER_LOOP
    if (inGame) {

        checkApple();
        checkCollision();
        move();
    }

    repaint();
    #endif
}

void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();
    QPainter qp(this);

    if ((key == Qt::Key_Left) && (angle != dir_right)) {
        angle = dir_left;
    }

    if ((key == Qt::Key_Right) && (angle != dir_left)) {
        angle = dir_right;
    }

    if ((key == Qt::Key_Up) && (angle != dir_down)) {
        angle = dir_up;
    }

    if ((key == Qt::Key_Down) && (angle != dir_up)) {
        angle = dir_down;
    }
    if (key == Qt::Key_Pause) {

        Pause ^= true;
    }

    QWidget::keyPressEvent(e);
}
