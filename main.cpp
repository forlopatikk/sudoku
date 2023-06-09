#include "sudoku.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SdkWindow w;
    w.setWindowIcon(QIcon("E:\\QTC\\Projects\\Sudoku\\sudoku.png"));
    QObject::connect(&w,SIGNAL(Close()),&a,SLOT(quit()));
    w.show();
    return a.exec();
}
