#pragma once
#include "main.h"
#include "CellBtn.h"
#include "menu.h"
#include "cell.h"

class Sudoku : public QWidget
{
    Q_OBJECT
public:
    Sudoku(QWidget* parent);

    static bool IsSandboxMode();
public slots:
    void Generate(int open_slots_count);
    void PlayTxtGame();
private slots:
    void Solve();
    void Help();
    void ClickedReturnBtn();
    void Check();

    void Update();
signals:
    void ReturnToMenu();
private:
    std::pair<int,int> FindError();

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *) override;

    QPushButton* _check;
    QPushButton* _solve;
    QPushButton* _return;
    QPushButton* _help;
    CellBtn* _cells[9][9];

    QTimer* _timer;
    uint16_t _seconds;
    QLabel* _timer_lbl;

    static inline bool _sandbox_mode = false;
    int _open_slots_count;
};


