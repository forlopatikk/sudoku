#ifndef MENU_H
#define MENU_H
#include "main.h"
#endif // MENU_H

class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu(QWidget* parent);
private:
    QPushButton* _play;
    QPushButton* _exit;
    QLineEdit* _setting;
private slots:
    void ClickedPlayBtn();
    void ClickedExitBtn();
signals:
    void Play(uint8_t setting);
    void Close();
};
