#ifndef GALLINA_H
#define GALLINA_H

#include <QVector>
#include <QPoint>

class Gallina
{
public:
    Gallina();
    Gallina(QPoint);
    ~Gallina();

    QPoint pos_inicial;
    QVector<QPoint> posible_moves_;

    void SetLastPos(QPoint);
};

#endif // GALLINA_H
