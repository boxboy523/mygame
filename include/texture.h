#ifndef MG_TEXTURE_H
#define MG_TEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <filesystem>

enum TextureError {
	TEXERR_WRONGPATH,
	TEXERR_IMAGE,
	TEXERR_TEXTURE,
	TEXERR_RENDERCLEAR,
	TEXERR_RENDORCOPY,
	TEXERR_INVALID,
	TEXERR_WRONGSRCSQ
};

class Texture {
private:
	std::filesystem::path path;
	SDL_Texture *texture;
	SDL_Renderer *renderer;
	bool valid;
	int width;
	int height;
public:
	Texture(std::filesystem::path _p, SDL_Renderer *_renderer);
	~Texture(void);
	bool Draw(const SDL_Rect *src, const SDL_Rect *dst);
	bool isValid(void) const;
	int getWidth(void) const;
	int getHeight(void) const;
};

#endif