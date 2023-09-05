#ifndef MG_MAIN_H
#define MG_MAIN_H
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#include <SDL.h>
#include <vector>
#include <string>
#include "window.h"
#include <filesystem>
#include "texture.h"

bool init(GameWindow *& window);
SDL_Surface *loadSurface(const std::string path, const SDL_PixelFormat *windowFmt);
SDL_Texture *loadTexture(const std::string path, SDL_Renderer *renderer);
void close(std::vector<SDL_Surface *> surfaceData, GameWindow *&window);

#endif