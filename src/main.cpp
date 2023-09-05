#include "main.h"
#include <cstdio>
#include <chrono>
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)

using namespace std;
using namespace chrono;
namespace fs = std::filesystem;

bool init(GameWindow *& window) {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = new GameWindow("mygame", SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_RENDERER);
	if (window == NULL) {
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	return success;
}

SDL_Surface *loadSurface(const string path, const SDL_PixelFormat *windowFmt) {
	SDL_Surface *convertedSurf = NULL;

	SDL_Surface *loadedSurf = IMG_Load(path.c_str());
	if (loadedSurf == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return NULL;
	}
	convertedSurf = SDL_ConvertSurface(loadedSurf, windowFmt, 0);
	if (convertedSurf == NULL) {
		printf("Unable to convert image %s! SDL Error: %s", path.c_str(), SDL_GetError());
	}

	SDL_FreeSurface(loadedSurf);

	return convertedSurf;
}

SDL_Texture *loadTexture(const string path, SDL_Renderer *renderer) {
	SDL_Texture *newTexture = NULL;

	SDL_Surface *loadedSurf = IMG_Load(path.c_str());
	if (loadedSurf == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return NULL;
	}

	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurf);
	if (newTexture == NULL){
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return NULL;
	}

	SDL_FreeSurface(loadedSurf);
	return newTexture;
}

void close(vector<SDL_Surface *> surfaceData, vector<SDL_Texture *> textureData, GameWindow *&window) {
	for (int i = 0; i<surfaceData.size(); i++) {
		SDL_FreeSurface(surfaceData[i]);
	}
	for (int i = 0; i<textureData.size(); i++) {
		SDL_DestroyTexture(textureData[i]);
	}

	delete window;
	window = NULL;

	SDL_Quit();
}

int main (int argc, char **argv) {
	GameWindow *window = NULL;
	vector<SDL_Surface *> surfaceData;
	vector<SDL_Texture *> textureData;

	surfaceData.push_back(NULL);
	textureData.push_back(NULL);

	SDL_Surface *& imgSurf = surfaceData[0];
	SDL_Texture *& imgTex = textureData[0];

	if (!init(window)) {
		printf("Failed to initalize!\n");
		return 1;
	}
	//imgSurf = loadSurface("image/zutomayo.png", window->getSurf()->format);
	//if (imgSurf == NULL) {
	//	printf( "Failed to load media!\n");
	//	return 1;
	//}
	//imgTex = loadTexture("image/tileset.png", window->getRenderer());
	//if (imgTex == NULL) {
	//	return 1;
	//}
	
	SDL_Event e;
	bool loop = true;
	system_clock::time_point prev_t = system_clock::now();
	const nanoseconds update_sec = nanoseconds(1000000000 / 60);
	nanoseconds lag = system_clock::now() - prev_t;
	nanoseconds elepsed;
	while(loop) {
		system_clock::time_point curr_t = system_clock::now();
		elepsed = curr_t - prev_t;
		prev_t = curr_t;
		lag += elepsed;
		while(SDL_PollEvent(&e)) {
			if( e.type == SDL_QUIT ) loop = false; 
			else if (e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_x:
					loop = false;
					break;

					default:
					break;
				}
			}
		}
		while (lag >= update_sec)
		{
			lag -= update_sec;
		}
		
		//SDL_BlitSurface(imgSurf, NULL, window->getSurf(), NULL);
		//SDL_RenderClear(window->getRenderer());
		//SDL_RenderCopy(window->getRenderer(), imgTex, NULL, NULL);
		window->update();
	}
	close(surfaceData, textureData, window);
	return 0;
}