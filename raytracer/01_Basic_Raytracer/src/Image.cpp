#include "Image.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include <cstring>
#include <vector>

namespace rt {

Image::~Image() {
    SDL_DestroyTexture(m_texture);
}

void Image::Initialize(uint32_t i_width, uint32_t i_height, SDL_Renderer* i_renderer) {
    m_width = i_width;
    m_height = i_height;

    m_rChannel.resize(m_width, std::vector<double>(m_height, 0.0));
    m_gChannel.resize(m_width, std::vector<double>(m_height, 0.0));
    m_bChannel.resize(m_width, std::vector<double>(m_height, 0.0));

    m_renderer = i_renderer;

    InitTexture();
}

void Image::SetPixel(int i_x, int i_y, double red, double green, double blue) {
    m_rChannel.at(i_x).at(i_y) = red;
    m_gChannel.at(i_x).at(i_y) = green;
    m_bChannel.at(i_x).at(i_y) = blue;
}

void Image::Display() {
    Uint32* pixels = new Uint32[m_width * m_height];

    memset(pixels, 0, m_width * m_height* sizeof(Uint32));

    for( int x = 0; x < m_width; x++) {
        for( int y = 0; y < m_height; y++) {
            pixels[(m_width * y) + x] = ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y));
        }
    }

    SDL_UpdateTexture(m_texture, nullptr, pixels, m_width * sizeof(Uint32));

    delete[] pixels;

    SDL_Rect srcRect {
        .x = 0,
        .y = 0,
        .w = static_cast<int>(m_width),
        .h = static_cast<int>(m_height),
    };
    SDL_Rect bounds = srcRect;
    SDL_RenderCopy(m_renderer, m_texture, &srcRect, &bounds);
}

Uint32 Image::ConvertColor(double red, double blue, double green) {

    uint8_t r = static_cast<uint8_t>(red);
    uint8_t g = static_cast<uint8_t>(green);
    uint8_t b = static_cast<uint8_t>(blue);
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    return (r << 24) | (g << 16) | (b << 8) | 255;
#else
    return (255 << 24) | (r << 16) | (g << 8) | b;
#endif
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
