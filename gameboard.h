#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <random>
#include <chrono>
#include <QTimer>

#include <iostream>


namespace Ui {
class GameBoard;
}

class GameBoard : public QWidget
{
    Q_OBJECT

public slots:
       void updateOgres();

signals:
       void game_over();

public:
    explicit GameBoard(QWidget *parent = 0, size_t board_size = 10, size_t ogre_speed = 10);
    ~GameBoard();

       void keyPressEvent(QKeyEvent *event);
       void paintEvent(QPaintEvent *e);
       void showEvent(QShowEvent *e);

       bool munchNumber();
       bool munchNumber(int x, int y);
       void updateMuncher(int px, int py, int nx, int ny);
       void updateAfterMunch(bool flag);
       bool isValidMunch(int x, int y);


private:
    Ui::GameBoard *ui;

    const QPixmap* muncher_image;
    QPixmap* ogre_image;

    QPoint *muncher_position;
    QPoint *ogre_positions;
    size_t number_ogres;

    // Top bar variables
    QLabel* game_type_value;
    QLabel* level_value;
    QWidget* Top;
    unsigned int lives_remaining;
    QLabel** lives;

    // Board Variables
    QWidget *Board;
    size_t board_size;
    size_t ogre_speed;
    QLabel** labels;
    int* values;

};

#endif // GAMEBOARD_H

