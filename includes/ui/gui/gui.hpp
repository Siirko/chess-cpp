#pragma once
#include "../../game.hpp"
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
    void handleEvents();
    void update();
    void render();
    void drawBoard();
    void drawPieces();
    void grabPiece();
    bool movePiece();
    void clean();
    std::shared_ptr<Piece> m_selectedPiece;
    void initTextureMap();
    bool isRunning() { return m_isRunning; }

  private:
    bool m_isRunning;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    SDL_Rect *m_sourceRectangle;
    SDL_Rect *m_destinationRectangle;
    std::map<std::string, SDL_Texture *> m_textureMap;
};
