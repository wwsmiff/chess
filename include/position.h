#pragma once

#include <cstdint>
#include <iostream>

struct Position
{
    int8_t file{};// vertical
    int8_t rank{};// horizontal

    bool operator!=(const Position &other)
    {
        return (this->file != other.file) || (this->rank != other.rank);
    }

    void operator--()
    {
        this->file--;
        this->rank--;
    }
};