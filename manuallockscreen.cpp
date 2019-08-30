#include "manuallockscreen.h"
#include "ui_manuallockscreen.h"

ManualLockScreen::ManualLockScreen(const QRect &initRect, QWidget *parent)
:QDialog(parent)
,ui(new Ui::ManualLockScreen)
,_timer(nullptr)
,_gameWindowRect(initRect)
{
    ui->setupUi(this);

    ui->x->setValue(_gameWindowRect.x());
    ui->y->setValue(_gameWindowRect.y());
    ui->width->setValue(_gameWindowRect.width());
    ui->height->setValue(_gameWindowRect.height());

    _timer = new QTimer(this);
    _timer->setInterval(100);
    _timer->setSingleShot(false);
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    _timer->start();
}

ManualLockScreen::~ManualLockScreen()
{
    if(_timer != nullptr)
    {
        delete _timer;
    }
    delete ui;
}

void ManualLockScreen::on_timer_timeout()
{
    QPixmap screenPixmap = QPixmap();
    QScreen * screen = QGuiApplication::primaryScreen();
    if(screen != 0)
    {
        screenPixmap = screen->grabWindow(0,
                                          _gameWindowRect.x(),
                                          _gameWindowRect.y(),
                                          _gameWindowRect.width(),
                                          _gameWindowRect.height());
    }
    _gameWindowImage.setPixmap(screenPixmap);
    _gameWindowImage.show();
}

void ManualLockScreen::on_x_valueChanged(int x)
{
    _gameWindowRect.setX(x);
}

void ManualLockScreen::on_y_valueChanged(int y)
{
    _gameWindowRect.setY(y);
}

void ManualLockScreen::on_width_valueChanged(int width)
{
    _gameWindowRect.setWidth(width);
}

void ManualLockScreen::on_height_valueChanged(int height)
{
    _gameWindowRect.setHeight(height);
}
