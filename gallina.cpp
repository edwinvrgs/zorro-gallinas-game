#include "gallina.h"

Gallina::Gallina()
{

}

Gallina::Gallina(QPoint point)
{
    pos_inicial = point;
}

Gallina::~Gallina()
{

}

void Gallina::SetLastPos(QPoint point)
{
    pos_inicial = point;
}

