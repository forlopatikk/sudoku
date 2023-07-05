#include "cell.h"

Cell::Cell(const int digit)
{
    _digit = digit;
    for (int i = 0; i < 9; i += 1) _free_digits[i] = true; // спочатку всі вільні
}

void Cell::Reset() // Скидає стан клітинки до початкового
{
    for (int i = 0; i < 9; i += 1) _free_digits[i] = true;
    _digit = 0;
}

int Cell::GetDigit() // повертає поточне значення цифри клітинки.
{
    return _digit;
}

void Cell::RemoveFD(int digit) // видаляє вказану цифру зі списку вільних цифр клітинки
{
    _free_digits[digit - 1] = false;
}

bool Cell::GenerateDigit() // генерація
{
    int fd_count = 0;
    for (int i = 0; i < 9; i += 1) fd_count += _free_digits[i];

    if (fd_count == 0) return false;

    int tmp = rand() % fd_count;
    int true_num = 0;
    while (true)
    {
        if (_free_digits[true_num])
        {
            if (tmp == 0) break;
            tmp -= 1;
        }
        true_num += 1;
    }

    _digit = true_num + 1;
    _free_digits[true_num] = false;
    return true;
}

void Cell::SetDigit(int digit) // set
{
    _digit = digit;
}
