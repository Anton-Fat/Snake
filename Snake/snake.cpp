#include <QPainter>
#include <QTime>

#include <QTimer>

#include <math.h>


#include "snake.h"
#include "python.h"

#include "player.h"

#include <QElapsedTimer>


/// \todo delete
#include <QDebug>

#define OUT_TIME

int Snake::fps = 50;

Snake::Snake(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet({"background-color:rgb(0, 30, 10);"

                  });

    m_map = new Map();
    gen.seed(time(0));
    inGame = true;




    m_pythons.push_back(make_unique<python>(QPoint(100,100)));
    m_pythons.at(0)->speed = 50; //250;

    m_pythons.push_back(make_unique<python>(QPoint(200,200)));
    m_pythons.at(1)->speed = 100;


    m_players.push_back(make_unique<Player>("Anton_p"));
    m_players.push_back(make_unique<Player>("Stas_p"));

    // Add players

    if (m_players.size() > 0) {

    m_players.at(0)->m_python = std::move(m_pythons.at(0)); //
    if(m_players.at(0)->m_python){
        m_players.at(0)->m_dict = control_1;
    }

    m_pythons.erase(m_pythons.begin());

    m_players.at(1)->m_python = std::move(m_pythons.at(0));
    if(m_players.at(1)->m_python){
        m_players.at(1)->m_dict = control_2;
    }

    m_pythons.erase(m_pythons.begin());

}

    m_pythons.push_back(make_unique<python>(QPoint(150,150)));
    m_pythons.back()->speed = 50;
    m_pythons.push_back(make_unique<python>(QPoint(250,250)));
    m_pythons.back()->speed = 50;


    debugShowCntObject();

    resize(m_map->getSize());
    loadImages();
    initGame();
}

Snake::~Snake()
{


    m_pythons.clear();
    //for (auto &m_python_o : m_python) {
    //    delete m_python;
    //}

//    for(int i = 0; i < max_count_python; ++i) { // python::count
//        if(m_python_t[i]) delete m_python_t[i];
//    }

    timer->stop();
    delete timer;
}
//==============================================================================
uint Snake::genValue(int &val, const int &N)
{
    //auto rd = std::random_device {};
    //mt_rand(time(0)); //gen(rd());
    //QTime time = QTime::currentTime();
    //qsrand((uint) time.msec());

    //std::uniform_int_distribution<int> dist(0, N-1);

    val = gen();

    return static_cast<uint>(val) % N; // http://www.quizful.net/post/random-number-generation-in-cpp11
}
//==============================================================================
void Snake::locateApple() {

    QSize map = m_map->getCountPoints();

    int val;

    pos_apple.setX(genValue(val, map.width()) * m_map->grid); // APPLE_SIZE
    pos_apple.setY(genValue(val, map.height()) * m_map->grid);
}
//==============================================================================
void Snake::debugShowCntObject()
{
    qDebug() << "Count animal : " << python::count <<
                " vector : " << m_pythons.size();
    qDebug() << "Count player : " << Player::count <<
                " vector : " << m_players.size();

}
//==============================================================================
std::vector<std::unique_ptr<Player>>::iterator Snake::getObject(string const& objName)
{
        return find_if(m_players.begin(), m_players.end(),
        [&](Ptr & obj){ return obj->name() == objName;}
                );

//    return remove_if(m_players.begin(), m_players.end(),
//                     [&](Ptr & obj){ return obj->name() == objName;}
//    );

}

//==============================================================================
void Snake::loadImages() {

    apple.load(":/res/images/apple_10.png");
}

//==============================================================================
void Snake::initGame() {

    locateApple();


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(period); // speed
    qDebug() << "period = " << period;


}
//==============================================================================
void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    doDrawing();
}

void Snake::doDrawing() {

    QPainter qp(this);

    if (inGame) {

        qp.drawImage(pos_apple.x(), pos_apple.y(), apple);

        for(int i = 0; i < m_players.size(); ++i) {
            if(m_players.at(i)) m_players.at(i)->m_python->draw(qp);
        }
        for(int i = 0; i < m_pythons.size(); ++i) {
            if(m_pythons.at(i)) m_pythons.at(i)->draw(qp);
        }


        if (Pause) {
            outText(qp, "Pause");
        }

    } else {

        gameOver(qp);
    }
}

//==============================================================================
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

//==============================================================================
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
//==============================================================================
void Snake::checkApple() {


    for(int i = 0; i < m_pythons.size(); ++i) {
        if(m_pythons.at(i))  {
            QPoint delta(m_pythons.at(i)->pos - pos_apple);
            if (delta.manhattanLength() < APPLE_SIZE/2){
               m_pythons.at(i)->addDot(m_pythons.at(i)->pointsReal.back());
               locateApple();
            }
        }
    }
    for(int i = 0; i < m_players.size(); ++i) {
        if(m_players.at(i))  {
            QPoint delta(m_players.at(i)->m_python->pos - pos_apple);
            if (delta.manhattanLength() < APPLE_SIZE/2){
                m_players.at(i)->m_python->addDot(m_players.at(i)->m_python->pointsReal.back());
                locateApple();
            }
        }
    }


}
//==============================================================================
void Snake::move() {

    for(int i = 0; i < m_players.size(); ++i) {
        if(m_players.at(i)) m_players.at(i)->m_python->move(m_map->getSize(), wall, period);
    }
    for(int i = 0; i < m_pythons.size(); ++i) {
        if(m_pythons.at(i))   m_pythons.at(i)->move(m_map->getSize(), wall, period);
    }

}
//==============================================================================
void Snake::checkCollision() {

//    for(int i = 0; i < m_players.size(); ++i) {
//        if(m_players.at(i)) inGame = m_players.at(i)->m_python->checkCollision(m_map->getSize(), m_python.at(i)->pointsReal);
//    }

    for(int i = 0; i < m_pythons.size(); ++i) {
        if(m_pythons.at(i))    inGame = m_pythons.at(i)->checkCollision(m_map->getSize(),
                                 m_pythons.at(i)->pointsReal);
    }
    if(!inGame) {
        ;
    }
}
//==============================================================================
void Snake::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

    if (inGame) {

        checkApple();
        checkCollision();
        move();
    }

    repaint();

}
//==============================================================================
void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();
    QPainter qp(this);

#ifdef OUT_TIME
    //QElapsedTimer timer;
    //timer.start();

    std::chrono::duration<double> durInsertTime(0);
    auto tp1 = std::chrono::high_resolution_clock::now();
#endif

 //   for (int i = 0; i < 100; ++i) {


        for (const auto& m_player : m_players)
        {
            if(m_player)
                m_player->action_angle(key);
        }
  //  }

#ifdef OUT_TIME
    auto tp2 = std::chrono::high_resolution_clock::now();
    durInsertTime = (tp2 - tp1);
    qDebug() << "Operation time vector took " <<
                std::chrono::duration_cast<std::chrono::microseconds>(durInsertTime).count() << "us\n";

    //qDebug() << "The slow operation took " << timer.elapsed() << " milliseconds";
#endif


    switch (e->key()) {
    case Qt::Key_Pause:
    case Qt::Key_P:

        Pause ^= true;
        break;
    case Qt::Key_I:

        debugShowCntObject();

        break;
    case Qt::Key_Insert:


        break;

    default:
        QWidget::keyPressEvent(e);
    }
    if(e->key() == Qt::Key_Delete)
    {

        eraseObject("Stas_p");

    }
}
//==============================================================================
void Snake::eraseObject(QString text)
{
    //std::vector<Ptr>::iterator object = getObject();
    auto object = getObject(text.toUtf8().constData());

    //m_players.erase(std::remove(m_players.begin(), m_players.end(), *object));
    if (object != m_players.end()) {
        m_players.erase(object);
    }
    //std::move(*object);
}
//==============================================================================
void Snake::resetAll()
{
            for(auto it = m_players.begin(); it != m_players.end();)
            {
                //use *it here
                bool needs_to_be_erased = true;

                if(needs_to_be_erased)
                    it = m_players.erase(it);
                else
                    ++it;
            }
}

//==============================================================================
