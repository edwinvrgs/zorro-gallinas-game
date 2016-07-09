#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QTimer>
#include <QBrush>
#include <QDebug>
#include <QPen>
#include "engine.h"
#include "tablero.h"
#include "escenajuego.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGraphicsScene *escena_principal_;
    EscenaJuego *escena_juego_;
    QMessageBox *mensaje_;

    QTimer *timer_;

    Tablero *tablero_;

    bool game_;

    void Reset();
    void InicializarComponentes();
    void CrearTablero();
    void Jugar(QString);
    bool PlayerMove();
    void ComputerMove();
    void CheckGame();

private slots:
    void on_actionSalir_triggered();
    void on_actionVs_Computer_triggered();
    void Refresh();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
