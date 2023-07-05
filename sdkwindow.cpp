#include "sdkwindow.h"

SdkWindow::SdkWindow() : // ініціалізація та налаштування вікна програми з двома екранами
    _m{new Menu(this)},
    _sdk{new Sudoku(this)},
    _main_widget{new QStackedWidget(this)}
{
    _main_widget->addWidget(_m);
    _main_widget->addWidget(_sdk);
    _main_widget->setCurrentWidget(_m);
    connect(_m,&Menu::Play,this,&SdkWindow::gotoSudoku);
    connect(_m,&Menu::Close,this,&SdkWindow::ClickedExitBtn);
    connect(_m,&Menu::PlayTxt,this,&SdkWindow::gotoTxtSudoku);
    connect(_sdk,&Sudoku::ReturnToMenu,this,&SdkWindow::gotoMenu);
    setCentralWidget(_main_widget);
    this->setMinimumSize(600,600);
    this->resize(600,600);
}

void SdkWindow::gotoMenu() // перехід до екрану меню
{
    _main_widget->setCurrentWidget(_m);
}

void SdkWindow::gotoSudoku(int setting) // перехід до екрану судоку
{
    _sdk->Generate(setting);
    _main_widget->setCurrentWidget(_sdk);
}

void SdkWindow::ClickedExitBtn() // обробник події натискання кнопки виходу
{
    emit Close();
}

void SdkWindow::gotoTxtSudoku()
{
    _sdk->PlayTxtGame();
    _main_widget->setCurrentWidget(_sdk);
}
