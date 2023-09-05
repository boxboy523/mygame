#include "texture.h"

using namespace std;
namespace fs = std::filesystem;

Texture::Texture(fs::path _p, SDL_Renderer *_renderer) {
	texture = NULL;
	path = _p;
	renderer = _renderer;
	valid = true;

	SDL_Surface *loadedSurf = NULL;

	try {
		if(!(fs::exists(path) && fs::is_regular_file(path))) throw TEXERR_WRONGPATH;
		SDL_Surface *loadedSurf = IMG_Load(path.c_str());
		if (loadedSurf == NULL) throw TEXERR_IMAGE;

		texture = SDL_CreateTextureFromSurface(renderer, loadedSurf);
		if (texture == NULL) throw TEXERR_TEXTURE;
		if (SDL_QueryTexture(texture, NULL, NULL, &width, &height) == -1) throw TEXERR_INVALID;
	} catch (TextureError err) {
		switch (err) {
		case TEXERR_WRONGPATH:
			printf("Texture init) %s is unavilable path", path.c_str());
			break;
		case TEXERR_IMAGE:
			printf("Texture init) Unable to load image %s! SDL_image Error: %s", path.c_str(), IMG_GetError());
			break;
		case TEXERR_TEXTURE:
			printf("Texture init) Unable to create texture from %s! SDL Error: ", path.c_str());
			break;
		case TEXERR_INVALID:
			printf("Texture init) invalid texture!");
			break;
		default:
			printf("Texture init) Unknown error!");
			break;
		}
		printf("%s\n",SDL_GetError());
		valid = false;
	}
	if (loadedSurf != NULL) SDL_FreeSurface(loadedSurf);
}

bool Texture::isValid(void) const {
	return valid;
}

int Texture::getWidth(void) const {
	if (valid)
		return width;
	else
		return -1;
}

int Texture::getHeight(void) const {
	if (valid)
		return height;
	else
		return -1;
}

bool Texture::Draw(const SDL_Rect *src, const SDL_Rect *dst) {
	try {
		if (!valid) throw TEXERR_INVALID;
		if (src != NULL && (src->h+src->y > height || src->y < 0)) throw TEXERR_WRONGSRCSQ;
		if (src != NULL && (src->w+src->x > height || src->x < 0)) throw TEXERR_WRONGSRCSQ;
		if (SDL_RenderClear(renderer) == -1) throw TEXERR_RENDERCLEAR;
		if (SDL_RenderCopy(renderer, texture, src, dst) == -1) throw TEXERR_RENDORCOPY;
	} catch (TextureError err) {
		switch (err) {
			case TEXERR_INVALID:
				printf("Texture::Draw) Invalid texture class!");
				break;
			case TEXERR_RENDERCLEAR:
				printf("Texture::Draw) Unable to clear renderer! SDL Error: ");
				break;
			case TEXERR_RENDORCOPY:
				printf("Texture::Draw) Unable to copy texture to renderer! SDL Error: ");
				break;
			case TEXERR_WRONGSRCSQ:
				printf("Texture::Draw) Wrong src squere!");
				break;
			default:
				printf("Texture::Draw) Unknown error!");
				break;
		}
		printf("%s\n",SDL_GetError());
		return false;
	}
	return true;
}

~Texture(void) {
	SDL_DestroyTexture(texture);
}