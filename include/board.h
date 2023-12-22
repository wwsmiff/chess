#pragma once

#include "config.h"
#include "piece.h"
#include "position.h"
#include "types.h"
#include <string>
#include <string_view>
#include <unordered_map>

/* clang-format off */

static std::unordered_map<uint8_t, char> m_board_map = {
    // Black pieces
    {Piece::Type::Black | Piece::Type::Pawn, 'p'},
    {Piece::Type::Black | Piece::Type::Bishop, 'b'},
    {Piece::Type::Black | Piece::Type::Knight, 'n'},
    {Piece::Type::Black | Piece::Type::Rook, 'r'},
    {Piece::Type::Black | Piece::Type::King, 'k'},
    {Piece::Type::Black | Piece::Type::Queen, 'q'},

    // White pieces
    {Piece::Type::White | Piece::Type::Pawn, 'P'},
    {Piece::Type::White | Piece::Type::Bishop, 'B'},
    {Piece::Type::White | Piece::Type::Knight, 'N'},
    {Piece::Type::White | Piece::Type::Rook, 'R'},
    {Piece::Type::White | Piece::Type::King, 'K'},
    {Piece::Type::White | Piece::Type::Queen, 'Q'},
};

/* clang-format on */

class Board
{
public:
    Board();
    void update();
    void draw();
    void render();
    void handle_events();
    bool is_running() const;
    void parse_fenstring();
    std::string generate_fenstring();

    friend class Piece;

protected:
    Window m_window{nullptr};
    Renderer m_renderer{nullptr};
    bool m_running{false};
    Position m_selected_square{-1, -1};
    Position m_original_selection{-1, -1};
    uint64_t m_piece_to_mv{Piece::Type::None};
    std::string m_fen{initial_board_fen_v};
    /* clang-format off */
    std::array<uint8_t, 64> m_board{
            Piece::Type::Black | Piece::Type::Rook, Piece::Type::Black | Piece::Type::Knight, Piece::Type::Black | Piece::Type::Bishop, Piece::Type::Black | Piece::Type::Queen, Piece::Type::Black | Piece::Type::King, Piece::Type::Black | Piece::Type::Bishop, Piece::Type::Black | Piece::Type::Knight, Piece::Type::Black | Piece::Type::Rook,
            Piece::Type::Black | Piece::Type::Pawn, Piece::Type::Black | Piece::Type::Pawn, Piece::Type::Black | Piece::Type::Pawn, Piece::Type::Black | Piece::Type::Pawn, Piece::Type::Black | Piece::Type::Pawn, Piece::Type::Black | Piece::Type::Pawn, Piece::Type::Black | Piece::Type::Pawn, Piece::Type::Black | Piece::Type::Pawn,
            Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None,
            Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None,
            Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None,
            Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None, Piece::Type::None,
            Piece::Type::White | Piece::Type::Pawn, Piece::Type::White | Piece::Type::Pawn, Piece::Type::White | Piece::Type::Pawn, Piece::Type::White | Piece::Type::Pawn, Piece::Type::White | Piece::Type::Pawn, Piece::Type::White | Piece::Type::Pawn, Piece::Type::White | Piece::Type::Pawn, Piece::Type::White | Piece::Type::Pawn,
            Piece::Type::White | Piece::Type::Rook, Piece::Type::White | Piece::Type::Knight, Piece::Type::White | Piece::Type::Bishop, Piece::Type::White | Piece::Type::Queen, Piece::Type::White | Piece::Type::King, Piece::Type::White | Piece::Type::Bishop, Piece::Type::White | Piece::Type::Knight, Piece::Type::White | Piece::Type::Rook,
    };
    /* clang-format on */
};