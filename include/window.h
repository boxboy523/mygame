#ifndef MG_WINDOW_H
#define MG_WINDOW_H
#include <SDL.h>
#include <string>

enum WindowOptn {
	WINDOW_RENDERER,
	WINDOW_SURFACE
};

enum WindowError {
	WINERR_WINDOW,
	WINERR_RENDERER,
	WINERR_SURFACE,
	WINERR_WRONGOPTN
};

class GameWindow {
	private:
		SDL_Window *window;
		SDL_Surface *surface;
		SDL_Renderer *renderer;
		bool valid;
		WindowOptn option;
	public:
		GameWindow(const std::string title, int width, int height, WindowOptn option);
		SDL_Window *getWindow(void);
		SDL_Surface *getSurf(void);
		SDL_Renderer *getRenderer(void);
		void update(void);
		~GameWindow(void);
};

#endif