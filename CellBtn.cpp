#include "sudoku.h"

CellBtn::CellBtn(QWidget* parent) : // стартовий колір білий + open btn + clicked to ChangeDigit
    QPushButton("0",parent),
    _digit{0},
    _is_open{true}
{
    connect(this,&CellBtn::clicked,this,&CellBtn::ChangeDigit);
    this->setStyleSheet("background-color:"+QColor(255,255,255).name());
}


int CellBtn::GetDigit() const // гетери
{
    return _digit;
}

bool CellBtn::IsLocked() const
{
    return not _is_open;
}

void CellBtn::SetDigit(const int digit) // оновлює текст кнопки, щоб відобразити нову цифру, і оновлює колір кнопки в залежності від цифри
{
    _digit = digit;
    setText(QString::number(_digit));
    UpdateColor();
}

void CellBtn::Lock() // локер клітинки. + change color
{
    if (_is_open)
    {
        _is_open = false;
        UpdateColor();
    }
}

void CellBtn::Open() // відкриває клітинку. + change color
{
    if (not _is_open)
    {
        _is_open = true;
        UpdateColor();
    }
}

void CellBtn::ChangeDigit() // Змінює цифру кнопки
{
    if (not _is_open) return;

    _digit += 1;
    if (_digit == 10)
    {
        _digit = 0;
    }
    setText(QString::number(_digit));
    UpdateColor();
}

void CellBtn::mousePressEvent(QMouseEvent* event) // : Обробляє подію натискання миші на кнопку.  SandBox mode [right clock / left click]
{
    if ((event->button() == Qt::RightButton) and Sudoku::IsSandboxMode())
    {
        if (_is_open) Lock();
        else Open();
    }
    QPushButton::mousePressEvent(event);
}

void CellBtn::resizeEvent(QResizeEvent*) // змінa розміру (set size font = 1/2 height)
{
    QFont tmp;
    tmp.setPixelSize(this->height()/2);
    this->setFont(tmp);
}

void CellBtn::UpdateColor() // Оновлює колір кнопки в залежності від стану кнопки та значення цифри
{
    if (IsLocked())
    {
        this->setStyleSheet("background-color:"+QColor(255,100,100).name()+";color:"+QColor(255,255,255).name());
        return;
    }
    if (_digit == 0)
    {
        this->setStyleSheet("background-color:"+QColor(255,255,255).name());
        return;
    }

    this->setStyleSheet("background-color:"+QColor(213/(_digit+1),25*(_digit+1),133).name());
}
