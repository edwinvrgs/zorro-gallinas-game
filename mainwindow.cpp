#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    game_ = false;
    ui->setupUi(this);
    InicializarComponentes();
    connect(timer_, SIGNAL(timeout()), this, SLOT(Refresh()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Reset()
{
    game_ = false;
    tablero_->Reset();
    ui->graphicsView->setScene(escena_principal_);
}

void MainWindow::InicializarComponentes()
{
    QIcon *icon = new QIcon(":/Imagenes/UNET");

    timer_ = new QTimer(this);
    mensaje_ = new QMessageBox(this);

    escena_principal_ = new QGraphicsScene(0,0,7*GROW,7*GROW,ui->graphicsView);
    escena_juego_ = new EscenaJuego(0,0,7*GROW,7*GROW,ui->graphicsView);
    
    escena_principal_->setBackgroundBrush(QBrush(Qt::black));
    escena_juego_->setBackgroundBrush(QBrush(Qt::white));

    mensaje_->setWindowTitle("Juego terminado");
    mensaje_->setIcon(QMessageBox::Information);
    mensaje_->setWindowIcon(*icon);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setScene(escena_principal_);
    ui->graphicsView->setAcceptDrops(true);

    CrearTablero();
}

void MainWindow::CrearTablero()
{
    tablero_ = new Tablero(0,0, escena_juego_);
}

void MainWindow::Jugar(QString oponente)
{
    if(game_)
        if(PlayerMove())
            ComputerMove(); //Esto hace el movimiento de la computadora si es que el jugador movio

    CheckGame();
}

bool MainWindow::PlayerMove()
{
    return tablero_->move_;
}

void MainWindow::ComputerMove()
{
    tablero_->move_ = false;
    tablero_->MoveChicken();
}

void MainWindow::CheckGame()
{
    if(tablero_->motor_logico_.closed_)
    {
        this->mensaje_->setText("Derrota. Has sido encajonado");
        this->mensaje_->exec();
        game_ = false;
        Reset();
    }

    if(tablero_->motor_logico_.chickens_out == 12)
    {
        this->mensaje_->setText("Victoria. Has comido 12 gallinas");
        this->mensaje_->exec();
        game_ = false;
        Reset();
    }
    if(tablero_->Empate())
    {
        this->mensaje_->setText("Empate. Ya no vas a poder comerte 12 gallinas");
        this->mensaje_->exec();
        game_ = false;
        Reset();
    }
}

//SLOTS

void MainWindow::on_actionSalir_triggered()
{
    this->close();
}

void MainWindow::on_actionVs_Computer_triggered()
{
    Reset();

    if(!game_)
    {
        game_ = true;
        timer_->start(60);
        ui->graphicsView->setScene(escena_juego_);
    }
}

void MainWindow::Refresh(){

    if(game_)
        Jugar("Computer");

    escena_juego_->update();

}
