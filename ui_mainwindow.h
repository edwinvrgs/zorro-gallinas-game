/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionVs_Computer;
    QAction *actionVs_Player;
    QAction *actionSalir;
    QAction *actionInstrucciones;
    QAction *actionAcerca_de;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuJuego;
    QMenu *menuNuevo_Juego;
    QMenu *menuAyuda;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(600, 640);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(600, 640));
        MainWindow->setMaximumSize(QSize(500, 500));
        MainWindow->setSizeIncrement(QSize(0, 0));
        MainWindow->setBaseSize(QSize(0, 0));
        QFont font;
        font.setFamily(QStringLiteral("DejaVu Sans"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Imagenes/UNET"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionVs_Computer = new QAction(MainWindow);
        actionVs_Computer->setObjectName(QStringLiteral("actionVs_Computer"));
        actionVs_Player = new QAction(MainWindow);
        actionVs_Player->setObjectName(QStringLiteral("actionVs_Player"));
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName(QStringLiteral("actionSalir"));
        actionInstrucciones = new QAction(MainWindow);
        actionInstrucciones->setObjectName(QStringLiteral("actionInstrucciones"));
        actionAcerca_de = new QAction(MainWindow);
        actionAcerca_de->setObjectName(QStringLiteral("actionAcerca_de"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 27));
        QFont font1;
        font1.setFamily(QStringLiteral("DejaVu Sans"));
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        menuBar->setFont(font1);
        menuJuego = new QMenu(menuBar);
        menuJuego->setObjectName(QStringLiteral("menuJuego"));
        menuNuevo_Juego = new QMenu(menuJuego);
        menuNuevo_Juego->setObjectName(QStringLiteral("menuNuevo_Juego"));
        QFont font2;
        font2.setItalic(false);
        font2.setKerning(true);
        menuNuevo_Juego->setFont(font2);
        menuAyuda = new QMenu(menuBar);
        menuAyuda->setObjectName(QStringLiteral("menuAyuda"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuJuego->menuAction());
        menuBar->addAction(menuAyuda->menuAction());
        menuJuego->addAction(menuNuevo_Juego->menuAction());
        menuJuego->addSeparator();
        menuJuego->addAction(actionSalir);
        menuNuevo_Juego->addAction(actionVs_Computer);
        menuAyuda->addAction(actionInstrucciones);
        menuAyuda->addAction(actionAcerca_de);
        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Zorro y Gallinas", 0));
        actionVs_Computer->setText(QApplication::translate("MainWindow", "vs. Computer", 0));
        actionVs_Player->setText(QApplication::translate("MainWindow", "vs. Player", 0));
        actionSalir->setText(QApplication::translate("MainWindow", "Salir", 0));
        actionInstrucciones->setText(QApplication::translate("MainWindow", "Instrucciones", 0));
        actionAcerca_de->setText(QApplication::translate("MainWindow", "Creditos", 0));
        menuJuego->setTitle(QApplication::translate("MainWindow", "Juego", 0));
        menuNuevo_Juego->setTitle(QApplication::translate("MainWindow", "Nuevo Juego", 0));
        menuAyuda->setTitle(QApplication::translate("MainWindow", "Ayuda", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
