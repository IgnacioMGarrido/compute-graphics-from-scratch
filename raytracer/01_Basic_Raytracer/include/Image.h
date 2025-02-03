#pragma once
#include <SDL2/SDL.h>
#include <vector>
namespace rt {

class Image {
public:
	~Image();
	void Initialize(uint32_t i_width, uint32_t i_height, SDL_Renderer* i_renderer);

	void SetPixel(int i_x, int i_y, Uint8 red, Uint8 green, Uint8 blue);

	void Display();

	inline uint32_t GetWidth() const { return m_width; }
	inline uint32_t GetHeight() const { return m_height; }
private:
	void InitTexture();

private:
	std::vector<Uint32> mPixelBuffer;
	uint32_t m_width = 0;
	uint32_t m_height = 0;

	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;
};

} //namespace rt
