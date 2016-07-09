#include "escenajuego.h"

EscenaJuego::EscenaJuego()
{
    chickens_out = 0;
}

EscenaJuego::EscenaJuego(QObject *parent):
    QGraphicsScene(parent)
{
    chickens_out = 0;
}

EscenaJuego::EscenaJuego(float x, float y, float w, float h, QObject *parent):
    QGraphicsScene(x, y, w, h, parent)
{
    chickens_out = 0;
}

EscenaJuego::~EscenaJuego()
{

}

void EscenaJuego::CheckCapture()
{

}


