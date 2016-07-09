#ifndef FICHA_H
#define FICHA_H
#define GROW 64

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QtGui>
#include <QLinkedList>
#include <limits.h>
#include "escenajuego.h"
#include "engine.h"

class EscenaJuego;

class Tablero : public QGraphicsItem
{
public:
    Tablero();
    Tablero(QGraphicsItem *parent = 0);
    Tablero(float, float, EscenaJuego*, QGraphicsItem *parent = 0);
    ~Tablero();

    bool move_;
    int x_;
    int y_;

    int mejor_valor_;

    int **table_;
    int **aux_table_;

    Engine motor_logico_;
    EscenaJuego *escena_padre_;

    QPoint pos_aux;

    //Variable que me guarda la mejor jugada
    Gallina mejor_jugada;

    void Reset();
    void MoveChicken();
    void Retry(QPoint, QPoint, int, int**);
    bool TodaviaPuedeComer();
    void PrintTable(int**);

    void SetCurrentTable();
    void ReturnTable();
    void GetMejorJugada();
    int CheckTable(int**);

    int DistanciaAlZorro(int**, QPoint);
    bool PuedeBajar(int **, QPoint);
    bool GallinaEnPeligro(int **, QPoint);
    int Comida(int **, QPoint);
    int EspaciosLibres(int **, QPoint);
    bool Empate();

    int Max(int);
    int Min(int);

    Movimiento MovimientoValido(QPoint);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);

};

#endif // FICHA_H
