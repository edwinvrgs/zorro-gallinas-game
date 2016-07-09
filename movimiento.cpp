#include "movimiento.h"

Movimiento::Movimiento()
{
    pos_inicial = QPoint(-1,-1);
    pos_final = QPoint(-1,-1);
    chicken_to_eat = QPoint(-1,-1);
    valid = false;
}

Movimiento::Movimiento(QPoint inicial, QPoint final, QPoint chicken)
{
    pos_inicial = inicial;
    pos_final = final;
    chicken_to_eat = chicken;
    valid = true;
}

Movimiento::~Movimiento()
{

}

void Movimiento::SetPoints(QPoint inicial, QPoint final, QPoint chicken)
{
    pos_inicial = inicial;
    pos_final = final;
    chicken_to_eat = chicken;
    valid = true;
}

