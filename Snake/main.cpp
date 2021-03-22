#include "snake.h"

#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);



    // create a scene
//    QGraphicsScene * scene = new QGraphicsScene();

//    QGraphicsRectItem * rect = new QGraphicsRectItem();
//    rect->setRect(0,0,100,100);

//    scene->addItem(rect);

//    QGraphicsView * view = new QGraphicsView(scene);

//    view->show();


    Snake window;
    window.setWindowTitle("Snake");
    window.show();

    return app.exec();
}
