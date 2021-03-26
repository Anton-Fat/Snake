#include <QPainter>
#include <QTime>

#include <QTimer>

#include <math.h>

#include "snake.h"
#include "python.h"


/// \todo delete
#include <QDebug>

int Snake::fps = 50;

Snake::Snake(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet({"background-color:rgb(0, 30, 10);"

                  });

    m_map = new Map();

    inGame = true;
    for(int i = 0; i < max_count_python; ++i) {
        m_python_t[i] = nullptr;
    }

    m_python = new python(QPoint(100,100));

    m_python_t[0] = m_python;

    m_python->speed = 250;

    m_python_test = new python(QPoint(200,200));

    m_python_t[1] = m_python_test;

    m_python_test->speed = 500;

    qDebug() << "Count python : " << python::count;

    qDebug() << "test " << round(2.4);
    qDebug() << "test " << round(2.6);

    resize(m_map->getSize());
    loadImages();
    initGame();
}

Snake::~Snake()
{
    if(m_python) delete m_python;



    if(m_python_test) delete m_python_test;
    timer->stop();
    delete timer;
}

void Snake::loadImages() {

    apple.load(":/res/images/apple_10.png");
}

void Snake::initGame() {

     locateApple();


     timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
     timer->start(period); // speed
     qDebug() << "period = " << period;


 }

 void Snake::paintEvent(QPaintEvent *e) {

     Q_UNUSED(e);

     doDrawing();
 }

 void Snake::doDrawing() {

     QPainter qp(this);

     if (inGame) {

         qp.drawImage(pos_apple.x(), pos_apple.y(), apple);


         for(int i = 0; i < python::count; ++i) {
             m_python_t[i]->draw(qp);
         }

         //m_python->draw(qp);
         //m_python_test->draw(qp);

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
     static int delay;
     if(!Pause){

         delay++;
         if (delay% 2 == 0) {

             if (inGame) {

                 move();
                 checkApple();
                 checkCollision();

             }
         }


     }
     repaint();

 }

 void Snake::checkApple() {

     if ((m_python->pos.x() == pos_apple.x()) && (m_python->pos.y() == pos_apple.y())) {

         m_python->pointsReal.push_back(m_python->pointsReal.back());
         locateApple();
     }
 }

 void Snake::move() {

     for(int i = 0; i < python::count; ++i) {
         m_python_t[i]->move(m_map->getSize(), wall, period);
     }
 }

 void Snake::checkCollision() {

     inGame = m_python->checkCollision(m_map->getSize(), m_python->pointsReal);

     if(!inGame) {
         ;
     }
 }

 void Snake::locateApple() {

     QSize map = m_map->getCountPoints();

     QTime time = QTime::currentTime();
     qsrand((uint) time.msec());

     int r = qrand() % map.width();
     pos_apple.setX(r * m_map->grid); // APPLE_SIZE

     r = qrand() % map.height();
     pos_apple.setY(r * m_map->grid);
 }

 void Snake::timerEvent(QTimerEvent *e) {

     Q_UNUSED(e);

     if (inGame) {

         checkApple();
         checkCollision();
         move();
     }

     repaint();

 }

 void Snake::keyPressEvent(QKeyEvent *e) {

     int key = e->key();
     QPainter qp(this);

     m_python->action_angle(key);

     switch (e->key()) {
     case Qt::Key_Pause:
     case Qt::Key_P:

         Pause ^= true;
         break;



     default:
         QWidget::keyPressEvent(e);
     }
 }
