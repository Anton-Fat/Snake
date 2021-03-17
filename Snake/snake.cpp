#include <QPainter>
#include <QTime>

#include <QTimer>

#include "snake.h"
#include "python.h"

Snake::Snake(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet({"background-color:rgb(0, 30, 10);"

                  });

    inGame = true;

    m_python = new python(QPoint(100,100));


    m_python->count;

    resize(B_WIDTH, B_HEIGHT);
    loadImages();
    initGame();
}

Snake::~Snake()
{
    if(m_python) delete m_python;
    timer->stop();
    delete timer;
}

void Snake::loadImages() {

    apple.load(":/res/images/apple_10.png");
}

void Snake::initGame() {

     locateApple();

     #ifdef TIMER_LOOP
     timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
     timer->start(m_python->speed);
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

         qp.drawImage(pos_apple.x(), pos_apple.y(), apple);

         m_python->draw(qp);

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

     if ((m_python->pos.x() == pos_apple.x()) && (m_python->pos.y() == pos_apple.y())) {

         m_python->points.push_back(m_python->points.back());
         locateApple();
     }
 }

 void Snake::move() {
    m_python->move(B_HEIGHT, B_WIDTH, wall);

 }

 void Snake::checkCollision() {

     inGame = m_python->checkCollision(B_HEIGHT, B_WIDTH, m_python->points);

     if(!inGame) {
         killTimer(timerId);
     }
 }

 void Snake::locateApple() {

     QTime time = QTime::currentTime();
     qsrand((uint) time.msec());

     int r = qrand() % RAND_POS;
     pos_apple.setX(r * APPLE_SIZE);

     r = qrand() % RAND_POS;
     pos_apple.setY(r * APPLE_SIZE);
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

     m_python->action_angle(key);

     if (key == Qt::Key_Pause) {

         Pause ^= true;
     }

     QWidget::keyPressEvent(e);
 }
