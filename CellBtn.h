#include "main.h"

class CellBtn : public QPushButton
{
    Q_OBJECT
public:
    CellBtn(QWidget* parent);

    int GetDigit() const;
    bool IsLocked() const;
    void SetDigit(int digit);
    void Lock();
    void Open();

private slots:
    void ChangeDigit();

private:
    void mousePressEvent(QMouseEvent*) override;
    void resizeEvent(QResizeEvent*) override;
    void UpdateColor();

    int _digit;
    bool _is_open;
};
