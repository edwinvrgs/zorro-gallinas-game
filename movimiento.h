#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include <QPoint>

class Movimiento
{
public:
    Movimiento();
    Movimiento(QPoint, QPoint, QPoint);
    ~Movimiento();

    QPoint pos_inicial;
    QPoint pos_final;
    QPoint chicken_to_eat;
    bool valid;

    void SetPoints(QPoint, QPoint, QPoint);

};

#endif // MOVIMIENTO_H
