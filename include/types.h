#pragma once

#include <functional>
#include <memory>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

using Window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>>;
using Renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>>;
using SVGTexture = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>;