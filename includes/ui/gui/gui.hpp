#pragma once
#include "../../game.hpp"
#include "ltexture.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <array>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

struct RGBA
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
};

RGBA getColorFromHEX(Uint32 hex)
{
    RGBA rgb;
    rgb.r = (hex >> 16) & 0xFF;
    rgb.g = (hex >> 8) & 0xFF;
    rgb.b = hex & 0xFF;
    return rgb;
}

RGBA tileColor(int i, int j)
{
    RGBA color;
    if ((i + j) % 2 == 0)
        color = getColorFromHEX(0x6D523B);
    else
        color = getColorFromHEX(0x90826c);
    return color;
}

class GUI : public Game
{
  public:
    GUI();
    ~GUI();
    void init();
    void run() override;
    void handleEvents(SDL_Event *event);
    void update();
    void render();
    void drawBoard();
    void drawPieces();
    void grabPiece();
    bool movePiece();
    void followMouse();
    void showPossibleMoves();
    void clean();
    std::shared_ptr<Piece> m_selectedPiece;
    int getWidth() const;
    int getHeight() const;
    int getSizeSquare() const;

  private:
    LTexture m_ltexture;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Rect *m_sourceRectangle;
    // Uint32 getColorFromHEX(SDL_Renderer *render, Uint32 hex);
};
