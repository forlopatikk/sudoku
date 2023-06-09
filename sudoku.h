#pragma once
#include "main.h"
#include "cellbtn.h"
#include "menu.h"

class Sudoku : public QWidget
{
    Q_OBJECT
public:
    Sudoku(QWidget* parent);
public slots:
    void Generate(uint8_t open_slots_count);
private slots:
    void Check();
    void Solve();
    void ClickedReturnBtn();
signals:
    void ReturnToMenu();
private:
    void paintEvent(QPaintEvent *) override;

    QPushButton* _check;
    QPushButton* _solve;
    QPushButton* _return;
    CellBtn* _cells[9][9];
};

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
    void gotoSudoku(uint8_t setting);
    void ClickedExitBtn();
signals:
    void Close();
};
