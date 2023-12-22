//
// Created by arvk on 21/11/23.
//

#include "../include/board.h"
#include "../include/config.h"
#include "../include/piece.h"
#include "../include/position.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>

namespace
{
    constexpr SDL_Color
    sdl_from_hex(uint32_t color)
    {
        return SDL_Color{.r = static_cast<uint8_t>(((color & 0xFF'00'00'00) >> 24)),
                         .g = static_cast<uint8_t>(((color & 0x00'FF'00'00) >> 16)),
                         .b = static_cast<uint8_t>(((color & 0x00'00'FF'00) >> 8)),
                         .a = static_cast<uint8_t>(color & 0x00'00'00'FF)};
    }
    std::ostream &operator<<(std::ostream &os, const Position &p)
    {
        os << "Position(" << static_cast<int32_t>(p.rank) << "," << static_cast<int32_t>(p.file) << ")";
        return os;
    }
};// namespace

Board::Board()
    : m_window{SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width_v, window_height_v, SDL_WINDOW_SHOWN), SDL_DestroyWindow},
      m_renderer{SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer},
      m_running{true}
{
}

void Board::draw()
{
    SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(m_renderer.get());

    for (int32_t col{}; col < nrows_v; col++)
    {
        for (int32_t row{}; row < ncols_v; row++)
        {
            bool is_light{static_cast<bool>(!((row + col) % 2))};
            constexpr SDL_Color light_color{sdl_from_hex(light_v)};
            constexpr SDL_Color dark_color{sdl_from_hex(dark_v)};

            SDL_Color square_color = is_light ? light_color : dark_color;

            SDL_Rect temp{row * square_size_v, col * square_size_v, square_size_v, square_size_v};
            SDL_SetRenderDrawColor(m_renderer.get(), square_color.r, square_color.g, square_color.b, square_color.a);
            SDL_RenderFillRect(m_renderer.get(), &temp);

            if (m_selected_square != Position{-1, -1})
            {
                if (m_selected_square.file == col && m_selected_square.rank == row)
                {
                    SDL_SetRenderDrawColor(m_renderer.get(), 0, 200, 40, 120);
                    SDL_RenderFillRect(m_renderer.get(), &temp);
                    if (m_board.at(m_selected_square.file * nrows_v + m_selected_square.rank) != Piece::Type::None)
                    {
                        m_original_selection = m_selected_square;
                        m_piece_to_mv = m_board.at(m_original_selection.file * nrows_v + m_original_selection.rank);
                    }
                }
            }
        }
    }

    if (m_original_selection != Position{-1, -1})
    {
        if (m_selected_square != m_original_selection)
        {
            m_board.at(m_selected_square.file * nrows_v + m_selected_square.rank) = static_cast<Piece::Type>(m_piece_to_mv);
            m_board.at(m_original_selection.file * nrows_v + m_original_selection.rank) = Piece::Type::None;
            m_original_selection = Position{-1, -1};
        }
        m_fen.clear();
        m_fen = this->generate_fenstring();
    }

    return;
}

void Board::render()
{
    SDL_RenderPresent(m_renderer.get());
    return;
}

void Board::handle_events()
{
    SDL_Event e{};
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            m_running = false;
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int32_t mouse_x{}, mouse_y{};
            SDL_GetMouseState(&mouse_x, &mouse_y);
            int8_t board_x{static_cast<int8_t>(mouse_x / square_size_v)}, board_y{static_cast<int8_t>(mouse_y / square_size_v)};
            m_selected_square = {.file = board_y, .rank = board_x};
        }
    }

    return;
}

bool Board::is_running() const
{
    return m_running;
}

void Board::parse_fenstring()
{
    /*
     * FEN String Rules
     * Upper case letters: describe white pieces
     * Lower case letters: describe black pieces
     * Empty squares: are described using numbers from 1 - 8
     * depending on the number of empty squares between two pieces
     */

    Position position{.file = 0, .rank = 0};

    for (const auto &c: m_fen)
    {
        Piece piece{Piece::Type::None};

        if (std::isdigit(c) && (c - '0') == 8)
            continue;
        else if (std::isdigit(c))
            position.rank += c - '0';
        else
        {
            switch (c)
            {
                case 'p':
                    piece = static_cast<Piece::Type>(Piece::Type::Black | Piece::Pawn);
                    piece.draw(this, position);
                    position.rank++;
                    break;
                case 'b':
                    piece = static_cast<Piece::Type>(Piece::Type::Black | Piece::Bishop);
                    piece.draw(this, position);
                    position.rank++;
                    break;
                case 'q':
                    piece = static_cast<Piece::Type>(Piece::Type::Black | Piece::Queen);
                    piece.draw(this, position);
                    position.rank++;
                    break;
                case 'r':
                    piece = static_cast<Piece::Type>(Piece::Type::Black | Piece::Rook);
                    piece.draw(this, position);
                    position.rank++;
                    break;
                case 'k':
                    piece = static_cast<Piece::Type>(Piece::Type::Black | Piece::King);
                    piece.draw(this, position);
                    position.rank++;
                    break;
                case 'n':
                    piece = static_cast<Piece::Type>(Piece::Type::Black | Piece::Knight);
                    piece.draw(this, position);
                    position.rank++;
                    break;
                case 'P':
                    piece = static_cast<Piece::Type>(Piece::White | Piece::Pawn);
                    piece.draw(this, position);
                    position.rank++;
                    break;
                case 'B':
                    piece = static_cast<Piece::Type>(Piece::White | Piece::Bishop);
                    piece.draw(this, position);
                    position.rank++;
                    break;
                case 'Q':
                    piece = static_cast<Piece::Type>(Piece::White | Piece::Queen);
                    piece.draw(this, position);
                    position.rank++;
                    break;
                case 'R':
                    piece = static_cast<Piece::Type>(Piece::White | Piece::Rook);
                    piece.draw(this, position);
                    position.rank++;
                    break;
                case 'K':
                    piece = static_cast<Piece::Type>(Piece::White | Piece::King);
                    piece.draw(this, position);
                    position.rank++;
                    break;
                case 'N':
                    piece = static_cast<Piece::Type>(Piece::White | Piece::Knight);
                    piece.draw(this, position);
                    position.rank++;
                    break;
                case '/':
                    position.file++;
                    piece.draw(this, position);
                    position.rank = 0;
                    break;
                default:
                    break;
            }
        }
    }
    return;
}

std::string Board::generate_fenstring()
{
    std::string fen{};
    Position position{};

    for (uint8_t i{}; i < ncols_v; ++i)
    {
        uint8_t empty_spaces{};
        std::string sub_fen{};

        for (uint8_t j{}; j < nrows_v; ++j)
        {
            if (m_board.at(i * nrows_v + j) == Piece::Type::None)
            {
                empty_spaces++;
                position.rank++;
            }
            else
            {
                if (empty_spaces)
                {
                    sub_fen.push_back(empty_spaces + '0');
                    empty_spaces = 0;
                }
                sub_fen.push_back(m_board_map.at(m_board.at(i * nrows_v + j)));
            }
        }
        if (empty_spaces == 8)
        {
            sub_fen.clear();
            sub_fen.push_back('8');
        }
        sub_fen.push_back('/');
        fen.insert(fen.end(), sub_fen.begin(), sub_fen.end());
    }

    fen.pop_back();

    return fen;
}