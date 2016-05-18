#ifndef MOVETHREAD_H
#define MOVETHREAD_H

#include <QThread>
#include <QRect>
#include <SFML/Graphics.hpp>

#include <QMutex>

using namespace sf;

class MoveThread : public QThread
{
public:
    MoveThread ();
    void setRect (QRect);
    void setSprite (Sprite*);

    void run();
signals:
    void resultReady(int);

private:
    QRect rect;
    Sprite* sprite;

    int time;
};

#endif // MOVETHREAD_H
