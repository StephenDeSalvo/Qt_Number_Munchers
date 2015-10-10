#include "mainwindow.h"
#include "gameboard.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::easy_game_begin() {
    board = new GameBoard(this,5,100);
    this->setCentralWidget(board);
}

void MainWindow::medium_game_begin() {
    board = new GameBoard(this,7,50);
    this->setCentralWidget(board);
}

void MainWindow::hard_game_begin() {
    board = new GameBoard(this,10,10);
    this->setCentralWidget(board);
}

void MainWindow::game_over() {

    // Take the current board game out of the central widget of MainWindow
    QWidget* wid = this->centralWidget();
    wid->setParent(nullptr);
    // Line above will delete the widget gracefully (no memory errors)

    // Display something which says that you lost, maybe display high score.

    // Reset the MainWindow with the initial startup screen
    ui->setupUi(this);


}




MainWindow::~MainWindow()
{
    delete ui;
}
