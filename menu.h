#include "main.h"

class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu(QWidget* parent);
private:
    QPushButton* _play;
    QPushButton* _exit;
    QPushButton* _my_txt_game;
    QLineEdit* _setting;
private slots:
    void ClickedPlayBtn();
    void ClickedExitBtn();
    void ClickedMyTxtBtn();
signals:
    void Play(int setting);
    void PlayTxt();
    void Close();
};
