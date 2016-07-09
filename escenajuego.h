#ifndef ESCENAJUEGO_H
#define ESCENAJUEGO_H

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QtGui>
#include <QLinkedList>
#include "tablero.h"

class EscenaJuego : public QGraphicsScene
{
public:

    EscenaJuego();
    EscenaJuego(QObject *parent = 0);
    EscenaJuego(float, float, float, float, QObject *parent = 0);

    ~EscenaJuego();

    int chickens_out;
    bool move_done;

    void CheckCapture();

};

#endif // ESCENAJUEGO_H
