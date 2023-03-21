#include "board.hpp"

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

Board::Board ()
{
    for (int row = 0; row < config::playfield_height; row++)
    {
        for (int col = 0; col < config::playfield_width; col++)
        {
            board_state[row][col] = BlockStatus::block_empty;
        }
    }
}

/**
 * @brief Позволяет получить тип тетрамино, помещенный в этом блоке
 * 
 * @param r строка 
 * @param c колонка
 * @return int 
 */
int Board::getTetromino (int r, int c)
{
    return int(board_state[r][c])-1;
}


/**
 * @brief Возвращает истину, если блок не занят 
 * 
 * @param r строка 
 * @param c колонка
 * @return true 
 * @return false 
 */
bool Board::isBlockFree (int r, int c)
{
    return (board_state[r][c] == BlockStatus::block_empty) ? true : false;
}


/**
 * @brief Возвращает истину, если возможно некое перемещение
 * 
 * @param p тетрамино
 * @return true 
 * @return false 
 */
bool Board::isPositionLegal (Piece p)
{
    for (int row = p.r; row < p.r+config::matrix_blocks; row++)
    {
        for (int col = p.c; col < p.c+config::matrix_blocks; col++)
        {
            // If outside of playfield limits
            if (col < 0 || col > (config::playfield_width-1) || row > (config::playfield_height-1))
            {
                if (p.getBlockType(row-p.r, col-p.c) != 0)
                {
                    return false;
                }
            }

            // If a block collides with a filled block
            if (row >= 0)
            {
                if (p.getBlockType(row-p.r, col-p.c) != 0 && !isBlockFree(row, col))
                {
                    return false;
                }
            }
        }
    }

    // No collisions found
    return true;
}

/**
 * @brief Сохранить тетрамино на поле
 * 
 * @param p тетрамино
 */
void Board::storePiece (Piece p)
{
    for (int row = p.r; row < p.r+config::matrix_blocks; row++)
    {
        for (int col = p.c; col < p.c+config::matrix_blocks; col++)
        {
            if (p.getBlockType(row-p.r, col-p.c) != 0)
            {
                board_state[row][col] = static_cast<BlockStatus>(1+p.piece_type);
            }
        }
    }
    pieces.push_back(p);
}


/**
 * @brief Очищает заполниную линию 
 * 
 */
void Board::clearFullLines()
{
    for (int row = 0; row < config::playfield_height; row++)
    {
        bool line_filled = true;
        for (int col = 0; col < config::playfield_width; col++)
        {
            if (isBlockFree(row, col))
            {
                line_filled = false;
            } 
        }
        if (line_filled)
        {
            deleteLine(row);
        }
    }
}

/**
 * @brief Возвращает истину, если игра закончилась
 * 
 * @return true 
 * @return false 
 */
bool Board::isGameOver ()
{
    bool game_over = false;
    for (int col = 0; col < config::playfield_width; col++)
    {
        if (board_state[0][col] != BlockStatus::block_empty || board_state[1][col] != BlockStatus::block_empty)
        {
            game_over = true;
            break;
        }
    }
    return game_over;
}

/*
 * ====================================
 * Private methods start here
 * ====================================
 */

/**
 * @brief Очищает заполненую сторочку и передаигает все блоки дальше
 * 
 * @param r 
 */
void Board::deleteLine (int r)
{
    for (int row = r; row > 0; row--)
    {
        for (int col = 0; col < config::playfield_width; col++)
        {
            board_state[row][col] = board_state[row-1][col];
        }
    }
}