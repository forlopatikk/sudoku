#include "cellbtn.h"

CellBtn::CellBtn(QWidget* parent) :
    QPushButton("0",parent),
    _digit{0},
    _is_open{true}
{
    connect(this,&CellBtn::clicked,this,&CellBtn::ChangeDigit);
    this->setStyleSheet("background-color:"+QColor(255,255,255).name());
}

uint8_t CellBtn::GetDigit() const
{
    return _digit;
}

bool CellBtn::IsLocked() const
{
    return !_is_open;
}

void CellBtn::SetDigit(const uint8_t digit)
{
    _digit = digit;
    setText(QString::number(_digit));
    UpdateColor();
}

void CellBtn::Lock()
{
    if (_is_open)
    {
        _is_open = false;
        setEnabled(false);
        UpdateColor();
    }
}

void CellBtn::Open()
{
    if (not _is_open)
    {
        _is_open = true;
        setEnabled(true);
        UpdateColor();
    }
}

void CellBtn::ChangeDigit()
{
    _digit += 1;
    if (_digit == 10)
    {
        _digit = 0;
    }
    setText(QString::number(_digit));
    UpdateColor();
}

void CellBtn::resizeEvent(QResizeEvent*)
{
    QFont tmp;
    tmp.setPixelSize(this->height()/2);
    this->setFont(tmp);
}

void CellBtn::UpdateColor()
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
