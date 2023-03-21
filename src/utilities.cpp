#include "utilities.hpp"

#include "piece.hpp"

/**
 * @brief Функция для смены двух разных блоков 
 * 
 * @param a 
 * @param b 
 */
void swap(Piece &a, Piece &b)
{
    Piece temp = a;
    a = b;
    b = temp;
}