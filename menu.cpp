#include "menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    _play{new QPushButton("Play!",this)},
    _exit{new QPushButton("Exit",this)},
    _setting{new QLineEdit(this)}
{
    QGridLayout* main_layout = new QGridLayout(this);
    main_layout->addWidget(_play,   1,1,1,1);
    main_layout->addWidget(_exit,   1,2,1,1);
    main_layout->addWidget(_setting,1,3,1,1);
    _setting->setValidator(new QIntValidator(0, 100, this) );
    _setting->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
    connect(_play,&QPushButton::clicked,this,&Menu::ClickedPlayBtn);
    connect(_exit,&QPushButton::clicked,this,&Menu::ClickedExitBtn);
    this->setLayout(main_layout);
}

void Menu::ClickedPlayBtn()
{
    uint8_t setting = _setting->text().toInt();
    if (setting > 81)
    {
        qWarning() << ">81!? srsly?";
        return;
    }
    emit Play(setting);
}

void Menu::ClickedExitBtn()
{
    emit Close();
}
