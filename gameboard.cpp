#include "gameboard.h"
#include "mainwindow.h"
#include "ui_gameboard.h"
#include <QPushButton>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);


GameBoard::GameBoard(QWidget *parent, size_t board_sz, size_t ogre_spd) :
    QWidget(parent),
    ui(new Ui::GameBoard), board_size(board_sz), ogre_speed(ogre_spd)
{
    ui->setupUi(this);


    Top = new QWidget;
    Top->setStyleSheet("QLabel { background-color : black; color : white; }");
    // This code sets up the Top bar
    //
    // M M M      Multiples of #     Level: #

    // This layout will space out the elements above
    QHBoxLayout *top_bar = new QHBoxLayout(Top);

    // Load up the image of the number muncher!


    // ****************CHANGE FILE PATH OF THE MUNCHER IMAGE HERE!! **************
//    QString fileName("/Users/PIC/Documents/Stephen\ DeSalvo/PIC\ 10\ C/Qt/Muncher.jpg");
//    QString fileName(":/Images/Muncher.jpg");
    QString fileName(":/Images/Muncher.jpg");
    muncher_image = new QPixmap(fileName);

    // Fix a total of 3 lives for now, can change later.
    // M M M

    // One life is currently playing, the others are listed above
    lives_remaining = 4;
    lives = new QLabel*[lives_remaining-1];
    // This line above is important, it is an array of QLabel POINTERS.
    // You have to input heap memory pointers for the memory management system to work properly.


    // Set the labels to have the muncher image, add to the top bar layout.
    for(size_t i=0;i<lives_remaining-1;i++) {
        lives[i] = new QLabel;
        //lives[i]->setPixmap(muncher_image);
        //lives[i]->setPixmap(QPixmap(fileName));
        lives[i]->setPixmap(*muncher_image);
        lives[i]->setMinimumSize(40,40);
        lives[i]->setMaximumSize(40,40);
        lives[i]->setScaledContents(true);
        top_bar->addWidget(lives[i]);
        //top_bar->addWi
    }


    // Add in some horizontal space before next labels
//    QSpacerItem* horizontal_space = new QSpacerItem(100,10);
    QSpacerItem* horizontal_space = new QSpacerItem(10,10);

    top_bar->addSpacerItem(horizontal_space);

    // M M M     Multiples of #
    QLabel* game_type_text = new QLabel("Multiples of ");
    game_type_value = new QLabel(QString::number(2)); // start with multiples of 2.

    top_bar->addWidget(game_type_text);
    top_bar->addWidget(game_type_value);

    // M M M     Multiples of #      Level: #
    QLabel* level_text = new QLabel("Level: ");
    level_value = new QLabel(QString::number(1)); // start with level 1.

    QSpacerItem* horizontal_space_2 = new QSpacerItem(*horizontal_space);
    // Add in some horizontal space before next labels
    top_bar->addSpacerItem(horizontal_space_2);
    top_bar->addWidget(level_text);
    top_bar->addWidget(level_value);




    // This code Creates the Board
    Board = new QWidget;
    labels = new QLabel*[board_size*board_size];
    values = new int[board_size*board_size];
    QGridLayout *SquareGrid = new QGridLayout(Board);

    SquareGrid->setGeometry(QRect());
    SquareGrid->setSpacing(0);

    // Random number generator for C++11
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(1,10);


    // Create each label for the board, initialize with random value.
    for(size_t i=0;i<board_size;i++) {
        for(size_t j=0;j<board_size;j++) {

            // Random values
            values[i*board_size+j] = distribution(generator);

            // Create label and set properties.
            labels[i*board_size+j] = new QLabel;
            labels[i*board_size+j]->setText(QString::number( values[i*board_size+j]));
            labels[i*board_size+j]->setMinimumSize(40,40);
            labels[i*board_size+j]->setMaximumSize(40,40);
            labels[i*board_size+j]->setStyleSheet("QLabel { background-color : black; color : white; }");
            labels[i*board_size+j]->setFrameStyle(3);
            labels[i*board_size+j]->setAlignment(Qt::AlignCenter);

            // Add label to the layout
            SquareGrid -> addWidget(labels[i*board_size+j] ,i,j);

        }
    }

    // Initialize the muncher at the top left corner, coordinate (0,0).
    muncher_position = new QPoint(0,0);
    labels[0]->setPixmap(*muncher_image);
    labels[0]->setScaledContents(true);

    Board->setFixedSize(400,400);


    // Now piece everything together
   // QWidget*& CoreWidget = this;
    // Central Widget composed of Top and Board
    //    Top
    // --------
    //   Board

    // Do not allow board to be resized, otherwise spacings get messed up
      setFixedSize(500,550);

      // Create a vertical box layout for the two pieces
      QVBoxLayout *piece_together = new QVBoxLayout;

      piece_together->addWidget(Top,0,Qt::AlignCenter);
      piece_together->addWidget(Board,0,Qt::AlignCenter);

      QPushButton* quit = new QPushButton("Quit");
      QObject::connect(quit, SIGNAL(clicked()), parent, SLOT(game_over()));

      piece_together->addWidget(quit);

      this->setLayout(piece_together);
      this->setStyleSheet("QLabel { background-color : black; color : white; }");

      // Set the CoreWidget as the central widget to the main window
      //setCentralWidget(CoreWidget);



      //QString ogre_filename("/Users/PIC/Documents/Stephen\ DeSalvo/PIC\ 10\ C/Qt/Ogre.jpg");
      QString ogre_filename(":/Images/Ogre.jpg");
      ogre_image = new QPixmap(ogre_filename);

      number_ogres = 4;
      ogre_positions = new QPoint[number_ogres];

      // Set ogres randomly just outside of the board.
      ogre_positions[0].setX(-1);
      ogre_positions[0].setY(distribution(generator)%board_size);

      ogre_positions[1].setX(board_size);
      ogre_positions[1].setY(distribution(generator)%board_size);

      ogre_positions[2].setY(-1);
      ogre_positions[2].setX(distribution(generator)%board_size);

      ogre_positions[3].setY(board_size);
      ogre_positions[3].setX(distribution(generator)%board_size);


      QTimer *timer = new QTimer(this);
      connect(timer, SIGNAL(timeout()), this, SLOT(updateOgres()));
      timer->start(ogre_speed);

      connect(this, SIGNAL(game_over()), parent, SLOT(game_over()));


}

GameBoard::~GameBoard()
{
    // According to
    delete [] values;
    delete [] ogre_positions;
    delete [] muncher_position;

    delete ui;
}


void GameBoard::keyPressEvent(QKeyEvent *event){

    int x = muncher_position->rx();
    int y = muncher_position->ry();

    switch (event->key()) {
    case Qt::Key_Left:
        if(muncher_position->rx() != 0)
            updateMuncher(x,y,x-1,y);

        break;
    case Qt::Key_Right:
        if(muncher_position->rx() != board_size-1)
            updateMuncher(x,y,x+1,y);

        break;
    case Qt::Key_Up:
        if(muncher_position->ry() != 0)
            updateMuncher(x,y,x,y-1);

        break;
    case Qt::Key_Down:
        if(muncher_position->ry() != board_size-1)
            updateMuncher(x,y,x,y+1);

        break;

    case Qt::Key_Space:
        munchNumber(x,y);
        break;
    default:
        QWidget::keyPressEvent(event);
    }

    // Need both lines to force a repaint.

    // This line forces processor to process all previously promised events.
    //QCoreApplication::processEvents();

    // This one QUEUES up a repaint
    //repaint();


    return;
}

void GameBoard::paintEvent(QPaintEvent *e) {

    int x = muncher_position->rx();
    int y = muncher_position->ry();

    labels[y*board_size+x]->setPixmap(*muncher_image);
    labels[y*board_size+x]->setScaledContents(true);

    for(size_t i=0;i<number_ogres;i++) {
        int px = ogre_positions[i].rx();
        int py = ogre_positions[i].ry();

        if(px >= 0 && py >= 0 && px < (int)board_size && py < (int)board_size) {
            labels[py*board_size+px]->setPixmap(*ogre_image);
            labels[py*board_size+px]->setScaledContents(true);
        }
    }


}


void GameBoard::showEvent(QShowEvent *e) {

    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(e);
}


void GameBoard::updateMuncher(int px, int py, int nx, int ny) {
    labels[py*board_size+px]->clear();
    if(values[py*board_size+px])
        labels[py*board_size+px]->setText(QString::number( values[py*board_size+px]));

    muncher_position->setX(nx);
    muncher_position->setY(ny);

//    return (px==nx)&&(py==ny);
}

bool GameBoard::munchNumber() {
    int x = muncher_position->rx();
    int y = muncher_position->ry();

    if(values[y*board_size+x]) {
        if(isValidMunch(x,y)) {
            updateAfterMunch(true);
            return true;
        }
        else {
            updateAfterMunch(false);
            return false;
        }
    }
    return true;
}

bool GameBoard::munchNumber(int x, int y) {

    if(values[y*board_size+x]) {
        if(isValidMunch(x,y)) {
            updateAfterMunch(true);
            return true;
        }
        else {
            updateAfterMunch(false);
            return false;
        }
    }
    return true;
}



bool GameBoard::isValidMunch(int x, int y) {

    if( values[y*board_size+x] % 2 == 0)
        return true;

    return false;
}


void GameBoard::updateAfterMunch(bool flag) {
    int x = muncher_position->rx();
    int y = muncher_position->ry();

    if(flag)
        values[y*board_size+x] = 0;
    else {
        values[y*board_size+x] = 0;
        if(lives_remaining > 1) {
            lives_remaining--;
            lives[lives_remaining-1]->clear();
        }
        else {
            this->game_over();
            // Game Over
        }
    }
}

void GameBoard::updateOgres() {


    //std::cout<< "Calling updateOrgres()\n"<<std::endl;

    std::uniform_real_distribution<double> p(0,1);
    std::uniform_int_distribution<int> x_or_y(0,1);
    std::uniform_int_distribution<int> increment(0,1);

    for(size_t i=0;i<number_ogres;i++) {

        int px = ogre_positions[i].rx();
        int py = ogre_positions[i].ry();
        //std::cout<<px<<py<<std::endl;

        if(px>=0 && py >= 0 && px<(int)board_size && py<(int)board_size) {
            labels[py*board_size+px]->clear();

            // If the value is not 0, redisplay the number.
            if(values[py*board_size+px])
                labels[py*board_size+px]->setText(QString::number( values[py*board_size+px]));
        }

        int nx = px;
        int ny = py;

        // If it is time to move this ogre, then
        if(p(generator) < 0.1) {

            if(x_or_y(generator) == 0) {
                nx = px + 2*increment(generator)-1;
                if(nx >= -1 && nx <= (int)board_size)
                    ogre_positions[i].setX(nx);
            }
            else {
                ny = py + 2*increment(generator)-1;
                if(ny >= -1 && ny <= (int)board_size)
                    ogre_positions[i].setY(ny);

            }

        }

    }

    repaint();
    QCoreApplication::processEvents();

    //checkIfMuncherIsEatenByOgre();

}
