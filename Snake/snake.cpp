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


    std::vector<std::unique_ptr<python>> pythons;


    m_python_t[0] = new python(QPoint(100,100));

    m_python_t[0]->speed = 50; //250;



    m_python_t[0]->m_dict.insert(pair<string,int>(m_python_t[0]->t_key_up, Qt::Key_Up));
    m_python_t[0]->m_dict.insert(pair<string,int>(m_python_t[0]->t_key_down, Qt::Key_Down));
    m_python_t[0]->m_dict.insert(pair<string,int>(m_python_t[0]->t_key_left, Qt::Key_Left));
    m_python_t[0]->m_dict.insert(pair<string,int>(m_python_t[0]->t_key_right, Qt::Key_Right));


    m_python_t[1] = new python(QPoint(200,200));

    m_python_t[1]->speed = 100; //500;

    m_python_t[1]->m_dict.insert(pair<string,int>(m_python_t[1]->t_key_up, Qt::Key_W));
    m_python_t[1]->m_dict.insert(pair<string,int>(m_python_t[1]->t_key_down, Qt::Key_S));
    m_python_t[1]->m_dict.insert(pair<string,int>(m_python_t[1]->t_key_left, Qt::Key_A));
    m_python_t[1]->m_dict.insert(pair<string,int>(m_python_t[1]->t_key_right, Qt::Key_D));


    qDebug() << "Count python : " << python::count;


    resize(m_map->getSize());
    loadImages();
    initGame();
}

Snake::~Snake()
{

    for(int i = 0; i < python::count; ++i) {
        if(m_python_t[i]) delete m_python_t[i];
    }

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
         if (delay% 1 == 0) {

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


     for(int i = 0; i < python::count; ++i) {
         if ((m_python_t[i]->pos.x() == pos_apple.x()) && (m_python_t[i]->pos.y() == pos_apple.y())) {

             m_python_t[i]->pointsReal.push_back(m_python_t[i]->pointsReal.back());
             locateApple();
         }
     }


 }

 void Snake::move() {

     for(int i = 0; i < python::count; ++i) {
         m_python_t[i]->move(m_map->getSize(), wall, period);
     }
 }

 void Snake::checkCollision() {

     for(int i = 0; i < python::count; ++i) {
     inGame = m_python_t[i]->checkCollision(m_map->getSize(), m_python_t[i]->pointsReal);
     }
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

     for(int i = 0; i < python::count; ++i) {
     m_python_t[i]->action_angle(key);
     }
     switch (e->key()) {
     case Qt::Key_Pause:
     case Qt::Key_P:

         Pause ^= true;
         break;



     default:
         QWidget::keyPressEvent(e);
     }
 }
