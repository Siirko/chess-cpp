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
    void drawTextInTile(int i, int j);
    void end();
    std::shared_ptr<Piece> m_selectedPiece;
    int getWidth() const;
    int getHeight() const;
    int getSizeSquare() const;

  private:
    TTF_Font *m_font;
    LTexture m_ltexture;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
};
