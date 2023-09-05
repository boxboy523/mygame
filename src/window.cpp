#include "window.h"
#include <string>

using namespace std;

GameWindow::GameWindow(const string title, int width, int height, WindowOptn _option){
	valid = true;
	try {
		window = SDL_CreateWindow(	"SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
									width, height, SDL_WINDOW_SHOWN);
		if (window == NULL)
			throw WINERR_WINDOW;
		option = _option;
		switch (option)
		{
			case WINDOW_RENDERER :
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				if (renderer == NULL) throw WINERR_RENDERER;
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
			break;

			case WINDOW_SURFACE :
				surface = SDL_GetWindowSurface(window);
				if (surface == NULL) throw WINERR_SURFACE;
			break;

			default :
				throw WINERR_WRONGOPTN;
				break;
		}
	} catch (WindowError err) {
		switch (err) {
			case WINERR_WINDOW:
				printf("GameWindow init) could not create window! SDL_Error: ");
				break;
			case WINERR_RENDERER:
				printf("GameWindow init) could not create renderer! SDL_Error: ");
				break;
			case WINERR_SURFACE:
				printf("GameWindow init) could not create surface! SDL_Error: ");
				break;
			case WINERR_WRONGOPTN:
				printf("GameWindow init) Invalid 'mode' parameter in GameWindow!! ");
				break;
			default :
				printf("GameWindow init) Unknown error");
		}
		printf("%s\n", SDL_GetError());
		valid = false;
	}
}

SDL_Window *GameWindow::getWindow(void) {
	if (valid)
		return window;
	else
		return NULL;
}

SDL_Surface *GameWindow::getSurf(void) {
	if (valid && option == WINDOW_SURFACE)
		return surface;
	else
		return NULL;
}

SDL_Renderer *GameWindow::getRenderer(void) {
	if (valid && option == WINDOW_RENDERER)
		return renderer;
	else
		return NULL;
}

void GameWindow::update(void) {
	if (option == WINDOW_RENDERER)
		SDL_RenderPresent( renderer );
	else if (option == WINDOW_SURFACE)
		SDL_UpdateWindowSurface(window);
}

GameWindow::~GameWindow(void) {
	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}