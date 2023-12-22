#pragma once
#include <cstdint>
#include <string_view>

constexpr int32_t window_width_v{768};
constexpr int32_t window_height_v{768};
constexpr uint8_t nrows_v{8};
constexpr uint8_t ncols_v{8};
constexpr int32_t square_size_v{window_width_v / nrows_v};
constexpr uint32_t light_v{0xE3CAA5FF};
constexpr uint32_t dark_v{0xAD8B73FF};
constexpr std::string_view initial_board_fen_v{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"};