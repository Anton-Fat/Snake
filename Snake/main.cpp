#include "snake.h"

#include <QApplication>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include <QDebug>
#include <thread>

void play();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::thread th(play);

    // windowPlayer

    // create a scene
//    QGraphicsScene * scene = new QGraphicsScene();

//    QGraphicsRectItem * rect = new QGraphicsRectItem();
//    rect->setRect(0,0,100,100);

//    scene->addItem(rect);

//    QGraphicsView * view = new QGraphicsView(scene);

//    view->show();


    Snake windowGame;
    windowGame.setWindowTitle("Snake");
    windowGame.show();

    return app.exec();
}
//==============================================================================
void play()
{
    QString pathSound = qApp->applicationDirPath() + "/";

    std::vector<string> fileData = {
        { "sounds/mambo_n_5.ogg" },
        { "sounds/diter_bolen.ogg" },
        { "sounds/honey_bunny.ogg" }
    };

    pathSound+= fileData.at(2).c_str();

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(pathSound.toUtf8().constData()))
    qDebug() << "File not load";

    sf::Sound sound;
    sound.setBuffer(buffer);

    sound.play();
    sound.setLoop(true);

    while (sound.getStatus() == sf::Sound::Playing)
    {
        sf::sleep(sf::seconds(0.1f));
    }

    //
    //std::this_thread::sleep_for(std::chrono::seconds(60));

    //th.join();

}
//==============================================================================
