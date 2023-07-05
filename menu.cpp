#include "menu.h"

Menu::Menu(QWidget *parent) : // створює кнопки play + exit + макет
    QWidget(parent),
    _play       {new QPushButton("Play!",this)},
    _exit       {new QPushButton("Exit",this)},
    _my_txt_game{new QPushButton("Load txt game",this)},
    _setting    {new QLineEdit(this)}
{
    QGridLayout* main_layout = new QGridLayout(this);
    main_layout->addWidget(_play,   1,1,1,1);
    main_layout->addWidget(_exit,   1,2,1,1);
    main_layout->addWidget(_setting,1,3,1,1);
    main_layout->addWidget(_my_txt_game,2,1,1,3);
    _setting->setValidator(new QIntValidator(0, 100, this) );
    _setting->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
    connect(_play,&QPushButton::clicked,this,&Menu::ClickedPlayBtn);
    connect(_exit,&QPushButton::clicked,this,&Menu::ClickedExitBtn);
    connect(_my_txt_game,&QPushButton::clicked,this,&Menu::ClickedMyTxtBtn);
    this->setLayout(main_layout);
}

void Menu::ClickedPlayBtn() // обробляє події натискання кнопки "play".
{
    int setting = _setting->text().toInt();
    if (setting > 81)
    {

        return;
    }
    emit Play(setting);
}

void Menu::ClickedExitBtn() // обробляє події натискання кнопки "exit".
{
    emit Close();
}

void Menu::ClickedMyTxtBtn()
{
    emit PlayTxt();
}
