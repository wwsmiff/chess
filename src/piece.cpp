//
// Created by arvk on 21/11/23.
//

#include <filesystem>

#include "../include/board.h"
#include "../include/config.h"
#include "../include/piece.h"
#include "../include/position.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace
{
    SVGTexture load_svg(Renderer &renderer, const std::filesystem::path &path)
    {
        std::unique_ptr<SDL_RWops, std::function<void(SDL_RWops *)>> svg_data{SDL_RWFromFile(path.c_str(), "r"), SDL_RWclose};
        std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *)>> temp_surface{IMG_LoadSVG_RW(svg_data.get()), SDL_FreeSurface};
        if (!temp_surface)
        {
            std::cerr << "Failed to load SVG from: " << path << std::endl;
            return nullptr;
        }
        return SVGTexture{SDL_CreateTextureFromSurface(renderer.get(), temp_surface.get()), SDL_DestroyTexture};
    }

};// namespace

Piece::Piece(Type type)
    : m_type{type}
{
}

void Piece::draw(Board *board, const Position &position)
{
    if (m_type == Type::None)
        return;
    static SVGTexture pieces_img = load_svg(board->m_renderer, "../assets/Chess_Pieces_Sprite_resized.svg");
    constexpr int32_t piece_dimension_v{540};
    bool is_white{static_cast<bool>((m_type & 0x80) && !(m_type & 0x40))};
    int32_t row_offset = ((m_type & 0x3F) - 1) * piece_dimension_v;
    int32_t col_offset = is_white ? 0 * piece_dimension_v : 1 * piece_dimension_v;
    SDL_Rect src = SDL_Rect{row_offset, col_offset, piece_dimension_v, piece_dimension_v};
    SDL_Rect dest = SDL_Rect{position.rank * square_size_v, position.file * square_size_v, 96, 96};
    SDL_RenderCopy(board->m_renderer.get(), pieces_img.get(), &src, &dest);

    return;
}