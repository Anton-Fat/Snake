#include "snake.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //Q_INIT_RESOURCE(Res);
    Snake window;


    window.setWindowTitle("Snake");
    window.show();

    return app.exec();
}
