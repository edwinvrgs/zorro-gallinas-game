#ifndef ENGINE_H
#define ENGINE_H

#include <QLinkedList>
#include <QVector>
#include "gallina.h"
#include "movimiento.h"

class Engine
{

public:
    Engine();
    ~Engine();

    int tablero_aux[7][7] = {
        {-1,-1,2,2,2,-1,-1},
        {-1,-1,2,2,2,-1,-1},
          {2,2,2,2,2,2,2},
          {2,0,0,0,0,0,2},
          {2,0,0,1,0,0,2},
        {-1,-1,0,0,0,-1,-1},
        {-1,-1,0,0,0,-1,-1}
    };

    int **tablero_logico_;
    int chickens_out;

    //Zorro
    QVector<Movimiento> movimientos_validos_;
    bool killed_;
    bool food_;
    bool closed_;
    QPoint pos_actual;

    //Gallinas
    QVector<Gallina> chickens_;

    void Reset();
    void MoveFox(QPoint&, Movimiento, int**, bool);
    void RetryFox(QPoint&, Movimiento move, int **table);
    void MoveChicken(QPoint, QPoint, int**);
    void GenerarMovimientosValidos(QPoint, int **, bool);
    void GenerarGallinas(int**);
    Movimiento CheckMove(QPoint, int, int, int**);
    Gallina CheckPoint(QPoint, int**);
};

#endif // ENGINE_H
