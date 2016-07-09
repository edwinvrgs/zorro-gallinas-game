#include "engine.h"
#include <QDebug>

Engine::Engine()
{
    tablero_logico_ = new int*[7];

    for (int k = 0; k < 7; ++k) {
        tablero_logico_[k] = new int[7];
    }


    for (int i = 0; i < 7; ++i)
        for(int j = 0; j < 7; j++)
        {
            tablero_logico_[i][j] = tablero_aux[i][j];
        }

    pos_actual = QPoint(3,4);

    killed_ = false;
    food_ = false;
    closed_ = false;
    chickens_out = 0;
}

Engine::~Engine()
{

}

void Engine::Reset()
{

    tablero_logico_ = new int*[7];

    for (int k = 0; k < 7; ++k) {
        tablero_logico_[k] = new int[7];
    }


    for (int i = 0; i < 7; ++i)
        for(int j = 0; j < 7; j++)
        {
            tablero_logico_[i][j] = tablero_aux[i][j];
        }

    pos_actual = QPoint(3,4);

    killed_ = false;
    food_ = false;
    closed_ = false;
    chickens_out = 0;
}

void Engine::MoveFox(QPoint &punto, Movimiento move, int **table, bool check)
{
    killed_ = false;

    QPoint move_fox = move.pos_final;
    QPoint to_eat = move.chicken_to_eat;

    int x = move_fox.x();
    int y = move_fox.y();

    int ex = to_eat.x();
    int ey = to_eat.y();

    if(!table[y][x])
    {
        table[punto.y()][punto.x()] = 0;
        table[y][x] = 1;
        punto = QPoint(x,y);

        if(to_eat != QPoint(-1,-1))
        {
            table[ey][ex] = 0;

            if(check)
                killed_ = true;
        }
    }
}

void Engine::RetryFox(QPoint &punto, Movimiento move, int **table)
{
    QPoint move_fox = move.pos_inicial;
    QPoint to_eat = move.chicken_to_eat;

    int x = move_fox.x();
    int y = move_fox.y();

    int ex = to_eat.x();
    int ey = to_eat.y();

    if(!table[y][x])
    {
        table[punto.y()][punto.x()] = 0;
        table[y][x] = 1;
        punto = QPoint(x,y);

        if(to_eat != QPoint(-1,-1))
            table[ey][ex] = 2;
    }
}

void Engine::MoveChicken(QPoint point, QPoint inicial, int **table)
{
    int x = point.x();
    int y = point.y();

    if(!table[y][x])
    {
        table[inicial.y()][inicial.x()] = 0;
        table[y][x] = 2;
    }
}

void Engine::GenerarMovimientosValidos(QPoint inicial, int **table, bool check)
{
    food_ = false;

    int x = inicial.x();
    int y = inicial.y();

    movimientos_validos_.clear();

    QPoint point(x,y);

    Movimiento movimiento;

    if(killed_)
        movimientos_validos_.push_back((Movimiento(point, point, QPoint(-1,-1))));

    if(y+1 < 7)
    {
        movimiento = CheckMove(point,0,1,table);

        if(movimiento.valid)
            movimientos_validos_.push_back(movimiento);
    }

    if(y-1 >= 0)
    {
        movimiento = CheckMove(point,0,-1,table);

        if(movimiento.valid)
            movimientos_validos_.push_back(movimiento);
    }

    if(x+1 < 7)
    {
        movimiento = CheckMove(point,1,0,table);

        if(movimiento.valid)
            movimientos_validos_.push_back(movimiento);
    }

    if(x-1 >= 0)
    {
        movimiento = CheckMove(point,-1,0,table);

        if(movimiento.valid)
            movimientos_validos_.push_back(movimiento);
    }

    if(y+1 < 7 && x+1 < 7)
    {
        movimiento = CheckMove(point,1,1,table);

        if(movimiento.valid)
            movimientos_validos_.push_back(movimiento);
    }

    if(y-1 >= 0 && x-1 >= 0)
    {
        movimiento = CheckMove(point,-1,-1,table);

        if(movimiento.valid)
            movimientos_validos_.push_back(movimiento);
    }

    if(y+1 < 7 && x-1 >= 0)
    {
        movimiento = CheckMove(point,-1,1,table);

        if(movimiento.valid)
            movimientos_validos_.push_back(movimiento);
    }

    if(y-1 >= 0 && x+1 < 7)
    {
        movimiento = CheckMove(point,1,-1,table);

        if(movimiento.valid)
            movimientos_validos_.push_back(movimiento);
    }

    if(!movimientos_validos_.count() && !killed_ && check)
        closed_ = true;

}

Movimiento Engine::CheckMove(QPoint point, int dx, int dy, int **table)
{
    Movimiento movimientos_validos_;
    QPoint to_eat;

    int x = point.x();
    int y = point.y();

    if(!table[y+dy][x+dx] && !killed_)
    {
        movimientos_validos_.SetPoints(QPoint(x,y), QPoint(x+dx,y+dy), QPoint(-1,-1));
    }
    else if(table[y+dy][x+dx] == 2)
    {
        to_eat = QPoint(x+dx,y+dy);

        dx *= 2;
        dy *= 2;

        if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
        {
            if(!table[y+dy][x+dx])
            {
                movimientos_validos_.SetPoints(QPoint(x,y), QPoint(x+dx,y+dy), to_eat);
                food_ = true;
            }
        }
    }

    return movimientos_validos_;
}

void Engine::GenerarGallinas(int **table)
{
    chickens_.clear();

    for (int i = 0; i < 7; ++i)
        for(int j = 0; j < 7; j++)
        {
            if(table[i][j] == 2)
            {
                Gallina gallina = CheckPoint(QPoint(j,i),table);

                if(gallina.pos_inicial != QPoint(-1,-1))
                    chickens_.push_back(gallina);
            }
        }
}

Gallina Engine::CheckPoint(QPoint point, int **table)
{
    int x = point.x();
    int y = point.y();

    Gallina gallina(point);
    bool exist = false;

    if(y+1 < 7 && !table[y+1][x])
    {
        gallina.posible_moves_.push_back(QPoint(x,y+1));
        exist = true;
    }

    if(x+1 < 7 && !table[y][x+1])
    {
        gallina.posible_moves_.push_back(QPoint(x+1, y));
        exist = true;
    }

    if(x-1 >= 0 && !table[y][x-1])
    {
        gallina.posible_moves_.push_back(QPoint(x-1, y));
        exist = true;
    }

    if(exist)
        return gallina;
    else
        return Gallina(QPoint(-1,-1));
}

