//
// Created by arvk on 21/11/23.
//

#pragma once

#include "../include/types.h"
#include <cstdint>

class Board;
struct Position;

class Piece
{
public:
    enum Type : uint8_t
    {
        None = 0x0,
        King = 0x1,
        Queen = 0x2,
        Bishop = 0x3,
        Knight = 0x4,
        Rook = 0x5,
        Pawn = 0x6,
        Black = 0x40,
        White = 0x80,

    };

    Piece(Type type);
    void draw(Board *board, const Position &position);
    void update();

protected:
    Type m_type{None};
};