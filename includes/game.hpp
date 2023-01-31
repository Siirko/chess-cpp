#pragma once
#include "board/board.hpp"
#include "pieces/piece.hpp"
#include <array>
#include <memory>
#include <vector>

class Game
{
  private:
    Board board;
    // 0 black, 1 white
    int turn;
    int num_turns;
    bool check;
    bool checkMate;
    std::vector<std::shared_ptr<Piece>> black_eaten_pieces;
    std::vector<std::shared_ptr<Piece>> white_eaten_pieces;
    void init();
    void forythGeneration(std::string fen);

  public:
    Game();
    ~Game();
    void run();
    void printInfo();
    std::shared_ptr<Piece> choosePiece(int x, int y);
    bool isCheck();
    bool isCheckMate();
    bool movePieceAt(std::shared_ptr<Piece> piece, int x, int y);
};