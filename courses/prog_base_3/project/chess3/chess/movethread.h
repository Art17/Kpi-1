#ifndef MOVETHREAD_H
#define MOVETHREAD_H

#include <QThread>
#include <QRect>
#include <SFML/Graphics.hpp>

using namespace sf;

class MoveThread : public QThread
{
public:
    MoveThread (QRect, Sprite*);

    void run();
signals:
    void resultReady(int);

private:
    QRect rect;
    Sprite* sprite;

    int time;
};

#endif // MOVETHREAD_H
