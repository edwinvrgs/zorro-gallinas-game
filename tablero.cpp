#include "tablero.h"
#include <QPainter>
#include <QTextItem>
#include <iostream>
#include <QtMath>

using namespace std;

Tablero::Tablero()
{

    escena_padre_ = NULL;
}

Tablero::Tablero(QGraphicsItem *parent):
    QGraphicsItem(parent)
{
    escena_padre_ = NULL;
}

Tablero::Tablero(float x, float y, EscenaJuego *parent_scene, QGraphicsItem *parent):
    QGraphicsItem(parent)
{
    x_ = x;
    y_ = y;

    move_ = false;

    escena_padre_ = parent_scene;
    escena_padre_->addItem(this);

    table_ = new int*[7];
    aux_table_ = new int*[7];

    for (int i = 0; i < 7; ++i)
    {
            table_[i] = new int[7];
            aux_table_[i] = new int[7];
    }

}

Tablero::~Tablero()
{

}

void Tablero::Reset()
{
    motor_logico_.Reset();
}

Movimiento Tablero::MovimientoValido(QPoint point)
{   
    motor_logico_.GenerarMovimientosValidos(motor_logico_.pos_actual, motor_logico_.tablero_logico_, 1);

    foreach(Movimiento movimiento, motor_logico_.movimientos_validos_)
        if(movimiento.pos_final == point)
            return movimiento;

    return Movimiento();
}

bool Tablero::TodaviaPuedeComer()
{
    bool opcion = false;

    if(motor_logico_.killed_ && motor_logico_.food_)
        opcion = true;
    else
    {
        motor_logico_.killed_ = false;
        motor_logico_.food_ = false;
    }

    return opcion;
}

void Tablero::PrintTable(int **table)
{
    for (int i = 0; i < 7; ++i)
    {
        for(int j = 0; j < 7; j++)
        {
            cout << "\t";
            if(table[i][j] == 2)
                cout << "@";
            else if(table[i][j] == 1)
                cout << "#";
            else if(!table[i][j])
                cout << "-";
        }

        cout << endl << endl;
    }

    cout << endl << endl << endl;
}

void Tablero::GetMejorJugada()
{
    //Inicializar el valor cada vez que vaya a conseguir una nueva jugada
    //Esto me dio unos problemas que ....
    mejor_valor_ = INT_MIN;

    int xvalor = 0;

    //Copiar el tablero por si acaso
    SetCurrentTable();

    //Llamo la funcion max indicandole la profundidad que deseo
    xvalor = Max(2);

    cout << "--- VALOR FINAL -----------> " << xvalor;
    cout << endl;

    cout << "TABLERO FINAL: ";
    PrintTable(motor_logico_.tablero_logico_);

}

void Tablero::SetCurrentTable()
{
    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j)
        {
            table_[i][j] = -9;
            table_[i][j] = motor_logico_.tablero_logico_[i][j];
            aux_table_[i][j] = motor_logico_.tablero_logico_[i][j];
        }

    pos_aux = motor_logico_.pos_actual;
}

void Tablero::ReturnTable()
{
    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j)
        {
            table_[i][j] = -9;
            table_[i][j] = aux_table_[i][j];
        }
}

//Funcion de evaluacion
int Tablero::CheckTable(int **table)
{
    int valor = 0, v_gallinas = 0, v_zorro = 0;

    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j)
        {
            if(table[i][j] == 2)
            {
                //Agregar valor por cada gallina que haya
                v_gallinas += 20;

                //Quitar bastante valor por cada gallina en peligro
                if(GallinaEnPeligro(table, QPoint(j,i)))
                    v_gallinas -= 20;

                //Prioriza las gallinas que puedan ir hacia abajo
                if(PuedeBajar(table, QPoint(j,i)) && !GallinaEnPeligro(table, QPoint(j,i+1)))
                    v_gallinas += 5;

                //Proriza las gallinas mas cercanas al zorro
                v_gallinas -= DistanciaAlZorro(table, QPoint(j,i));

            }

            if(table[i][j] == 1)
            {
                //Agregarle valor al zorro si tiene alguien para comer
                v_zorro += Comida(table, QPoint(j,i));

                //Agregar por cada espacio que tenga para mover
                v_zorro += EspaciosLibres(table, QPoint(j,i));
            }
        }

    //Cuando el valor es grande es porque es una buena jugada para las gallinas
    valor = v_gallinas - v_zorro;

    return valor;
}

int Tablero::DistanciaAlZorro(int **table, QPoint punto)
{
    int x1 = punto.x();
    int y1 = punto.y();

    int x2;
    int y2;

    int distancia = 0;

    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j)
            if(table[i][j] == 1)
            {
                x2 = j;
                y2 = i;
            }

    int xf = qPow((x2 - x1), 2);
    int yf = qPow((y2 - y1), 2);

    distancia = qSqrt(xf + yf);

    return distancia+1;
}

bool Tablero::PuedeBajar(int **table, QPoint punto)
{
    if(punto.y()+1 < 7 && table[punto.y()+1][punto.x()] == 0)
        return true;
    else
        return false;
}

bool Tablero::GallinaEnPeligro(int **table, QPoint punto)
{
    int x = punto.x();
    int y = punto.y();

    if(y+1 < 7 && y-1 >= 0 && table[y+1][x] == 1 && !table[y-1][x])
        return true;
    if(y+1 < 7 && y-1 >= 0 && table[y-1][x] == 1 && !table[y+1][x])
        return true;
    if(x+1 < 7 && x-1 >= 0 && table[y][x+1] == 1 && !table[y][x-1])
        return true;
    if(x+1 < 7 && x-1 >= 0 && table[y][x-1] == 1 && !table[y][x+1])
        return true;
    if(x+1 < 7 && x-1 >= 0 && y+1 < 7 && y-1 >= 0 && table[y+1][x+1] == 1 && !table[y-1][x-1])
        return true;
    if(x+1 < 7 && x-1 >= 0 && y+1 < 7 && y-1 >= 0 && table[y+1][x-1] == 1 && !table[y-1][x+1])
        return true;
    if(x+1 < 7 && x-1 >= 0 && y+1 < 7 && y-1 >= 0 && table[y-1][x+1] == 1 && !table[y+1][x-1])
        return true;
    if(x+1 < 7 && x-1 >= 0 && y+1 < 7 && y-1 >= 0 && table[y-1][x-1] == 1 && !table[y+1][x+1])
        return true;

    return false;
}

int Tablero::Comida(int **table, QPoint punto)
{
    int comida = 0;
    int puntos = 10;

    int dx;
    int dy;

    int x = punto.x();
    int y = punto.y();

    dx = 0;
    dy = 1;

    if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
        if(table[y+dy][x+dx] == 2)
        {
            dx *= 2;
            dy *= 2;

            if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
                if(!table[y+dy][x+dx])
                    comida += puntos;

        }

    dx = 0;
    dy = -1;

    if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
        if(table[y+dy][x+dx] == 2)
        {
            dx *= 2;
            dy *= 2;

            if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
                if(!table[y+dy][x+dx])
                    comida += puntos;

        }

    dx = 1;
    dy = 0;

    if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
        if(table[y+dy][x+dx] == 2)
        {
            dx *= 2;
            dy *= 2;

            if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
                if(!table[y+dy][x+dx])
                    comida += puntos;

        }

    dx = -1;
    dy = 0;

    if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
        if(table[y+dy][x+dx] == 2)
        {
            dx *= 2;
            dy *= 2;

            if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
                if(!table[y+dy][x+dx])
                    comida += 2;

        }

    dx = 1;
    dy = 1;

    if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
        if(table[y+dy][x+dx] == 2)
        {
            dx *= 2;
            dy *= 2;

            if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
                if(!table[y+dy][x+dx])
                    comida += puntos;

        }

    dx = -1;
    dy = -1;

    if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
        if(table[y+dy][x+dx] == 2)
        {
            dx *= 2;
            dy *= 2;

            if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
                if(!table[y+dy][x+dx])
                    comida += puntos;
        }

    dx = 1;
    dy = -1;

    if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
        if(table[y+dy][x+dx] == 2)
        {
            dx *= 2;
            dy *= 2;

            if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
                if(!table[y+dy][x+dx])
                    comida += puntos;

        }

    dx = -1;
    dy = 1;

    if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
        if(table[y+dy][x+dx] == 2)
        {
            dx *= 2;
            dy *= 2;

            if(x+dx >= 0 && y+dy >= 0 && x+dx < 7 && y+dy < 7)
                if(!table[y+dy][x+dx])
                    comida += puntos;

        }

    return comida;
}

int Tablero::EspaciosLibres(int **table, QPoint punto)
{
    int espacios = 0;
    int puntos = 5;

    int x = punto.x();
    int y = punto.y();

    if(y-1 >= 0 && !table[y-1][x])
        espacios += puntos;
    if(y+1 < 7 && !table[y+1][x])
        espacios += puntos;
    if(x-1 >= 0 && !table[y][x-1])
        espacios += puntos;
    if(x+1 < 7 && !table[y][x+1])
        espacios += puntos;
    if(x-1 >= 0 && y-1 >= 0 && !table[y-1][x-1])
        espacios += puntos;
    if(x+1 < 7 && y-1 >= 0 && !table[y-1][x+1])
        espacios += puntos;
    if(x-1 >= 0 && y+1 < 7 && !table[y+1][x-1])
        espacios += puntos;
    if(x+1 < 7 && y+1 < 7 && !table[y+1][x+1])
        espacios += puntos;

    return espacios;
}

bool Tablero::Empate()
{
    if(motor_logico_.tablero_logico_[5][2] == 2)
        if(motor_logico_.tablero_logico_[5][3] == 2)
            if(motor_logico_.tablero_logico_[5][4] == 2)
                if(motor_logico_.tablero_logico_[6][2] == 2)
                    if(motor_logico_.tablero_logico_[6][3] == 2)
                        if(motor_logico_.tablero_logico_[6][4] == 2)
                            return true;
    return false;
}

int Tablero::Max(int nivel)
{
    //Condicion de parada
    if(!nivel)
    {
        int valor = CheckTable(motor_logico_.tablero_logico_);
        //qDebug() << "-- VALOR HEURISTICO DE MAX ----------->" << valor;
        return valor;
    }

    //int valor = INT_MIN;
    int xvalor = 0;

    //Generar movimientos posibles
    motor_logico_.GenerarGallinas(motor_logico_.tablero_logico_);

    //Un ciclo por cada gallina y luego por cada jugada que puede hacer esa gallina
    foreach(Gallina chicken, motor_logico_.chickens_)
    {
        foreach(QPoint point, chicken.posible_moves_)
        {
            //Mover la gallina
            motor_logico_.MoveChicken(point, chicken.pos_inicial, motor_logico_.tablero_logico_);

            cout << "Tablero Max: " << endl;
            PrintTable(motor_logico_.tablero_logico_);

            //Recursividad
            xvalor = Min(nivel-1);

            cout << "- VALOR MAX - en el nivel " << nivel << " -> " << xvalor;
            cout << endl;

            //Se guarda el mejor valor con jugada y todo
            if(xvalor > mejor_valor_)
            {
                mejor_valor_ = xvalor;
                mejor_jugada.posible_moves_.clear();
                mejor_jugada.posible_moves_.push_back(point);
                mejor_jugada.pos_inicial = chicken.pos_inicial;
            }

            //Quitar el movmimento hecho
            motor_logico_.MoveChicken(chicken.pos_inicial, point, motor_logico_.tablero_logico_);
        }
    }

    return mejor_valor_;
}

//Min es practicamente lo mismo que max solo que mueve al zorro
int Tablero::Min(int nivel)
{
    //Condicion de parada
    if(!nivel)
    {
        int valor = CheckTable(motor_logico_.tablero_logico_);
        //qDebug() << "-- VALOR HEURISTICO DE MAX ----------->" << valor;
        return valor;
    }

    int peor_valor_ = INT_MAX;
    int xvalor = 0;

    //Generar movimientos posibles
    motor_logico_.GenerarMovimientosValidos(pos_aux, motor_logico_.tablero_logico_, 0);

    //El ciclo por cada movimiento
    foreach(Movimiento movimiento, motor_logico_.movimientos_validos_)
    {
        //Mover el zorro
        motor_logico_.MoveFox(pos_aux, movimiento, motor_logico_.tablero_logico_, 0);

        cout << "Tablero Min: " << endl;
        PrintTable(motor_logico_.tablero_logico_);

        //Volver a llamar aumentando el nivel
        xvalor = Max(nivel-1);

        cout << "- VALOR MIN - en el nivel " << nivel << " -> " << xvalor;
        cout << endl;

        if(xvalor < peor_valor_)
            peor_valor_ = xvalor;

        //Quitar movimiento del zorro
        motor_logico_.RetryFox(pos_aux, movimiento, motor_logico_.tablero_logico_);
    }

    return peor_valor_;
}

void Tablero::MoveChicken()
{
     //Esto era para hacer las jugadas al azar
   /* srand(time(NULL));

    motor_logico_.GenerarGallinas(motor_logico_.tablero_logico_);

    int c = rand() % motor_logico_.chickens_.count();
    Gallina chicken = motor_logico_.chickens_[c];

    c = rand() % chicken.posible_moves_.count();
    QPoint punto = chicken.posible_moves_[c];

    motor_logico_.MoveChicken(punto, chicken.pos_inicial, motor_logico_.tablero_logico_);*/


    //Aplicar min max para una variable de tipo gallina que esta como atributo
    GetMejorJugada();
    motor_logico_.MoveChicken(mejor_jugada.posible_moves_.takeFirst(),
                              mejor_jugada.pos_inicial,
                              motor_logico_.tablero_logico_);

}

void Tablero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    int i, j;

    QPen lapiz_elipse(Qt::darkBlue);
    lapiz_elipse.setWidth(10);

    painter->setPen(lapiz_elipse);
    painter->drawEllipse(-32,-31, 8*GROW, 8*GROW);

    QPen lapiz(Qt::white);
    QBrush fondo(Qt::gray);

    lapiz.setWidth(3);
    painter->setPen(lapiz);
    painter->setBrush(fondo);

    for (i = 0; i < 7; ++i)
        for (j = 0; j < 7; ++j)
        {
            QRect rect(j*GROW, i*GROW, GROW, GROW);

            if(motor_logico_.tablero_logico_[i][j] != -1)
                painter->drawRect(rect);
        }

    for (i = 0; i < 7; ++i)
        for (j = 0; j < 7; ++j)
            if(motor_logico_.tablero_logico_[i][j] == 2)
                painter->drawImage(j*GROW, i*GROW, (new QPixmap(":/Imagenes/Chicken"))->toImage());
            else if (motor_logico_.tablero_logico_[i][j] == 1)
                painter->drawImage(j*GROW, i*GROW, (new QPixmap(":/Imagenes/Fox"))->toImage());

}

QRectF Tablero::boundingRect() const
{
    return QRectF(x_,y_,escena_padre_->width(),escena_padre_->height());
}

void Tablero::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int x = (int) event->pos().x()/GROW;
    int y = (int) event->pos().y()/GROW;

    Movimiento movimiento;

    qDebug() << "X: " << x << "| Y: " << y;

    if(x >= 0 && y >= 0 && x < 7 && y < 7 && motor_logico_.tablero_logico_[y][x] != -1)
    {

        movimiento = MovimientoValido(QPoint(x,y));

        if(movimiento.valid)
        {
            motor_logico_.MoveFox(motor_logico_.pos_actual, movimiento, motor_logico_.tablero_logico_, 1);

            if(motor_logico_.killed_)
                motor_logico_.chickens_out++;

            motor_logico_.GenerarMovimientosValidos(motor_logico_.pos_actual, motor_logico_.tablero_logico_, 1);

            if(TodaviaPuedeComer())
                move_ = false;
            else
                move_ = true;
        }
    }

    event->accept();
}
