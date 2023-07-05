#include "main.h"
// Цей клас потрібен тільки для того, щоб створювати та вирішувати судоку
class Cell
{
private:
    bool _free_digits[9];
    int _digit; // 0 - нема числа
public:
    Cell(const int digit = 0);
    void Reset();
    int GetDigit();
    void RemoveFD(int digit);
    bool GenerateDigit();
    void SetDigit(int digit);
};
