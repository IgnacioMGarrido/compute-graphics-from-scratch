#pragma once
#include <SDL2/SDL.h>
#include <vector>
namespace rt {

class Image {
public:
	~Image();
	void Initialize(uint32_t i_width, uint32_t i_height, SDL_Renderer* i_renderer);

	void SetPixel(int i_x, int i_y, double red, double green, double blue);

	void Display();

	inline uint32_t GetWidth() const { return m_width; }
	inline uint32_t GetHeight() const { return m_height; }
private:

	Uint32 ConvertColor(double red, double green, double blue);
	void InitTexture();

private:
	std::vector<std::vector<double>> m_rChannel;
	std::vector<std::vector<double>> m_gChannel;
	std::vector<std::vector<double>> m_bChannel;

	std::vector<Uint32> mPixelBuffer;
	uint32_t m_width = 0;
	uint32_t m_height = 0;

	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;
};

} //namespace rt
