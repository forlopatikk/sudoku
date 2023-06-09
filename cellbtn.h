#ifndef CELLBTN_H
#define CELLBTN_H
#include "main.h"
#endif // CELLBTN_H

class CellBtn : public QPushButton
{
    Q_OBJECT
public:
    CellBtn(QWidget* parent = 0);

    uint8_t GetDigit() const;
    bool IsLocked() const;
    void SetDigit(uint8_t digit);
    void Lock();
    void Open();

private slots:
    void ChangeDigit();

private:
    void resizeEvent(QResizeEvent *event) override;
    void UpdateColor();

    uint8_t _digit;
    bool _is_open;
};
