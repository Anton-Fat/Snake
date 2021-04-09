#include <QPainter>
#include <QTime>

#include <QTimer>

#include <math.h>

#include "snake.h"
#include "python.h"

#include "player.h"


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


    m_players.push_back(make_unique<Player>("Anton"));

    m_python_t[0] = new python(QPoint(100,100));

    m_python_t[0]->speed = 50; //250;

    m_python_t[1] = new python(QPoint(200,200));

    m_python_t[1]->speed = 100; //500;

    // Add players

    if (m_players.size() > 0) {

    m_players.at(0)->m_python = m_python_t[0];

    if(m_players.at(0)->m_python){
        m_players.at(0)->addDict(m_players.at(0)->t_key_up, Qt::Key_Up);
        m_players.at(0)->addDict(m_players.at(0)->t_key_down, Qt::Key_Down);
        m_players.at(0)->addDict(m_players.at(0)->t_key_left, Qt::Key_Left);
        m_players.at(0)->addDict(m_players.at(0)->t_key_right, Qt::Key_Right);
    }

}

    m_player_2 = new Player("Stas");
    m_player_2->m_python = m_python_t[1];

    if(m_player_2->m_python){
        m_player_2->addDict(m_player_2->t_key_up, Qt::Key_W);
        m_player_2->addDict(m_player_2->t_key_down, Qt::Key_S);
        m_player_2->addDict(m_player_2->t_key_left, Qt::Key_A);
        m_player_2->addDict(m_player_2->t_key_right, Qt::Key_D);
    }


    qDebug() << "Count animal : " << python::count;
    qDebug() << "Count player : " << Player::count;

    resize(m_map->getSize());
    loadImages();
    initGame();
}

Snake::~Snake()
{

    for(int i = 0; i < max_count_python; ++i) { // python::count
        if(m_python_t[i]) delete m_python_t[i];
    }

    timer->stop();
    delete timer;
}

std::vector<std::unique_ptr<Player>>::iterator Snake::getObject(string const& objName)
{
        return find_if(m_players.begin(), m_players.end(),
        [&](Ptr & obj){ return obj->name() == objName;}
                );

//    return remove_if(m_players.begin(), m_players.end(),
//                     [&](Ptr & obj){ return obj->name() == objName;}
//    );

}

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


        for(int i = 0; i < max_count_python; ++i) {
            if(m_python_t[i]) m_python_t[i]->draw(qp);
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


    for(int i = 0; i < max_count_python; ++i) {
        if(m_python_t[i]) { if ((m_python_t[i]->pos.x() == pos_apple.x()) && (m_python_t[i]->pos.y() == pos_apple.y())) {

            m_python_t[i]->pointsReal.push_back(m_python_t[i]->pointsReal.back());
            locateApple();
            }
        }
    }


}
//==============================================================================
void Snake::move() {

    for(int i = 0; i < max_count_python; ++i) {
        if(m_python_t[i])  m_python_t[i]->move(m_map->getSize(), wall, period);
    }
}

void Snake::checkCollision() {

    for(int i = 0; i < max_count_python; ++i) {
        if(m_python_t[i])   inGame = m_python_t[i]->checkCollision(m_map->getSize(), m_python_t[i]->pointsReal);
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


    for (const auto& m_player : m_players)
    {
        if(m_player)
        m_player->action_angle(key);
    }

    if(m_player_2) {
        m_player_2->action_angle(key);
    }

    switch (e->key()) {
    case Qt::Key_Pause:
    case Qt::Key_P:

        Pause ^= true;
        break;
    case Qt::Key_Delete:




        //std::vector<Ptr>::iterator object = getObject();


//        m_players.erase(std::remove(m_players.begin(), m_players.end(), *object));

//      m_players.erase(std::remove_if(m_players.begin(), m_players.end(),
//         [&](Ptr& pi){ return pi->name() == "Stas"; }), m_players.end());

//      m_players.erase(std::remove_if(m_players.begin(), m_players.end(),
//         [](Ptr& pi){ return pi->name() == "Anton"; }), m_players.end());


//        if(m_players.size() != 0)
//        {
//           //
//           m_players.erase();
//        }


        break;
    case Qt::Key_Insert:


        break;

    default:
        QWidget::keyPressEvent(e);
    }
    if(e->key() == Qt::Key_Delete)
    {
//                //std::vector<Ptr>::iterator object = getObject();
//        auto object = getObject("Anton");

//                //m_players.erase(std::remove(m_players.begin(), m_players.end(), *object));
//        if (object != m_players.end()) {
//        m_players.erase(object);
//        }
//                //std::move(*object);

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
}
//==============================================================================
