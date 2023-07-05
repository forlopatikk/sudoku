#ifndef SDKWINDOW_H
#define SDKWINDOW_H

#endif // SDKWINDOW_H
#include "main.h"
#include "sudoku.h"

class SdkWindow : public QMainWindow
{
    Q_OBJECT
public:
    SdkWindow();
private:
    Menu* _m;
    Sudoku* _sdk;
    QStackedWidget* _main_widget;
private slots:
    void gotoMenu();
    void gotoSudoku(int setting);
    void ClickedExitBtn();
    void gotoTxtSudoku();
signals:
    void Close();
};
