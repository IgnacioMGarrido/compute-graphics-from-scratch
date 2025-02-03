#include "Image.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include <vector>

namespace rt {

Image::~Image() {
    SDL_DestroyTexture(m_texture);
}

void Image::Initialize(uint32_t i_width, uint32_t i_height, SDL_Renderer* i_renderer) {
    m_width = i_width;
    m_height = i_height;

    m_renderer = i_renderer;

    mPixelBuffer = std::vector<Uint32>(m_width * m_height, 0);
    InitTexture();
}

void Image::SetPixel(int i_x, int i_y, Uint8 red, Uint8 green, Uint8 blue) {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    mPixelBuffer.at(i_y * m_width + i_x) = (red << 24) | (green << 16) | (blue << 8) | 255;
#else
    mPixelBuffer.at(i_y * m_width + i_x) = (255 << 24) | (red << 16) | (green << 8) | blue;
#endif

}

void Image::Display() {
    SDL_UpdateTexture(m_texture, nullptr, mPixelBuffer.data(), m_width * sizeof(Uint32));

    SDL_Rect bounds = {0, 0, static_cast<int>(m_width), static_cast<int>(m_height)};
    SDL_RenderCopy(m_renderer, m_texture, nullptr, &bounds);
}

void Image::InitTexture() {

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rMask = 0xff000000;
    Uint32 gMask = 0x00ff0000;
    Uint32 bMask = 0x0000ff00;
    Uint32 aMask = 0x000000ff;
#else
    Uint32 rMask = 0x000000ff;
    Uint32 gMask = 0x0000ff00;
    Uint32 bMask = 0x00ff0000;
    Uint32 aMask = 0xff000000;
#endif

    SDL_DestroyTexture(m_texture);

    SDL_Surface* tmpSurface = SDL_CreateRGBSurface(0, m_width, m_height, sizeof(Uint32), rMask, gMask, bMask, aMask);

    m_texture = SDL_CreateTextureFromSurface(m_renderer, tmpSurface);

    SDL_FreeSurface(tmpSurface);

}
} // namespace
